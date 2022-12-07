#include "../Include/miniRT.h"

double	calc_root(double top_roco, double toprd, double h_2, double t)
{
	double	root;

	if (t < 0)
		root = -top_roco / toprd;
	else
		root = (h_2 - top_roco) / toprd;
	return (root);
}

double	vec_dot(t_point u, t_point v)
{
	double	distance;

	distance = (u.x * v.x) + (u.y * v.y) + (u.z * v.z);
	return (distance);
}


void print_point(t_point p)
{
	printf("p.x = [%f] | ", p.x);
	printf("p.y = [%f] | ", p.y);
	printf("p.z = [%f]\n", p.z);
	printf("************************************************\n");

}

void ft_swap(double *x, double *y)
{
	double z;

	z = *x;
	*x = *y;
	*y = z;
}

double	git_root(t_Cylinder cy, t_point hHat, t_ray ray, double *m)
{
	double t;
	double	t1;
	double	t2;

	t = DBL_MAX;
	t1 = (-cy.Q.b + cy.Q.sqrt_disc) / (2 * cy.Q.a);
	t2 = (-cy.Q.b - cy.Q.sqrt_disc) / (2 * cy.Q.a);
	if (t1 > t2)
		ft_swap(&t1, &t2);
	double m1 = (v_dot(ray.direction, v_mul(t1, hHat))) + v_dot(cy.X, hHat);
	double m2 = (v_dot(ray.direction, v_mul(t2, hHat))) + v_dot(cy.X, hHat);
	if (m1 > EPSILON && m1 <= cy.height)
	{
		t = t1;
		*m = m1;
	}
	else if (m2 > EPSILON && m2 <= cy.height)
	{
		t = t2;
		*m = m2;
	}
	return (t);
}

t_color convet(size_t *c)
{
	t_color re;

	re.r = (int)c[0];
	re.g = (int)c[1];
	re.b = (int)c[2];
	return re;
}

bool	intersectPlaneDisk(t_Plane disk, t_ray ray, double *t)
{
	int	i;
	double tmin;
	double hd;

	i = -1;
	hd = EPSILON;
	ray.direction = normalizing(ray.direction);
	double p = v_dot(disk.ray.direction, ray.direction);
	t_point resultOfSub = v_sub(disk.ray.origin, ray.origin);
	tmin = v_dot(resultOfSub, disk.ray.direction) / p;
	if (tmin < EPSILON || tmin == DBL_MAX)
	{
		*t = DBL_MAX;
		return false;
	}
	*t = tmin;
	return true;
}

bool intersectDisk(t_Plane Disk, t_ray ray, double radius, double *t) 
{ 
    if (intersectPlaneDisk(Disk, ray, t)) { 
        t_point p = v_adding(ray.origin, v_mul(*t, ray.direction)); 
        t_point v = v_sub(p, Disk.ray.origin); 
        double d2 = length_squared(v);
        if (d2 <= radius)
			return true;
	} 
    return false; 
} 

bool check_disk_cylinder(t_Cylinder cy, t_ray ray, t_hit *hit, double *T, double M)
{
	double t = DBL_MAX;


	cy.Disk_bottom.ray.origin = v_sub(cy.top, v_mul(-cy.height, cy.Disk_top.ray.direction));
	cy.Disk_bottom.ray.direction = cy.Disk_top.ray.direction;
	if (intersectDisk(cy.Disk_bottom, ray, cy.redius, &t))
	{
		if (t < *T)
		{
			*T = t;
			hit->obj_color = convet(cy.color);
			hit->hit_pos = v_adding(ray.origin, v_mul(t, ray.direction));
			hit->normal = normalizing(v_sub(v_sub(hit->hit_pos, cy.Disk_bottom.ray.origin), v_mul(t, cy.Disk_bottom.ray.	direction)));
			return true;
		}
	}
//
//	else if (intersectDisk(cy.Disk_top, ray, cy.redius, &t))
//	{
//		if (t < *T && t < cy.t_min){
//			*T = t;
//			hit->obj_color = convet(cy.color);
//			hit->hit_pos = v_adding(ray.origin, v_mul(t, ray.direction));
//			hit->normal = normalizing(v_sub(v_sub(hit->hit_pos, cy.Disk_top.ray.origin), v_mul(t, cy.Disk_top.ray.direction)));
//			return true;
//		}
//	}


	return false;
}

void	quadratic_cal()
{
	cy[i].Q.a = v_dot(ray.direction, rrayay.direction) - pow(v_dot(ray.direction, hHat), 2);
	cy[i].Q.b = 2 * (v_dot(ray.direction, cy[i].X) - (v_dot(ray.direction, hHat) * v_dot(cy[i].X, hHat)));
	cy[i].Q.c = v_dot(cy[i].X, cy[i].X) - pow(v_dot(cy[i].X, hHat), 2) - pow(cy[i].redius, 2);
	cy[i].Q.discriminant = pow(cy[i].Q.b, 2) - (4 * cy[i].Q.a * cy[i].Q.c);
	return ;
}

bool	cylinder_intersection(t_minirt *rt, t_ray ray, double *t, t_hit *hit)
{
	int i = -1;
	double M;
	double t_m;
	t_point A;
	t_point B;
	t_point hHat;

	*t = DBL_MAX;
	t_m = DBL_MAX;
	t_Cylinder *cy=  rt->Cylinder;
	ray.direction = normalizing(ray.direction);
	while (++i < rt->Data->shape.cy)
	{
		A = v_mul(cy[i].height, cy[i].ray.direction); //to find orign of top
		B = normalizing(A); //to find direction of top
		cy[i].top = v_adding(v_mul(cy[i].height, B), cy[i].ray.origin); //find top point
		cy[i].X = v_sub(ray.origin, cy[i].top);
		hHat = normalizing(v_sub(cy[i].top, v_adding(cy[i].top, v_mul(cy[i].height, cy[i].ray.direction))));

		if (cy[i].Q.discriminant < EPSILON)
				continue ;
		cy[i].Q.sqrt_disc = sqrt(cy[i].Q.discriminant);
		t_m = git_root(cy[i], hHat, ray, &M);
		cy[i].t_min = t_m;
		cy[i].Disk_top.ray.origin = cy[i].top;
		cy[i].Disk_top.ray.direction = hHat;
		 if (t_m < *t)
		{
			*t= cy[i].t_min;
			hit->obj_color = convet(cy[i].color);
			hit->hit_pos = v_adding(ray.origin, v_mul(*t, ray.direction));
			hit->normal = normalizing(v_sub(v_sub(hit->hit_pos, cy[i].top), v_mul(M, hHat)));
			if (rt->Mlx->mouse)
				rt->Mlx->obj.index = i;
		}
		else if (check_disk_cylinder(cy[i], ray, hit, t, M)){
			if (rt->Mlx->mouse)
				rt->Mlx->obj.index = i;
		}
	}
	if (*t == DBL_MAX)
		return false;
	return true;
}
