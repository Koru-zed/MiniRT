#include "../Include/miniRT.h"

/*
 *  ∗ identifier: cy
	* cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255
	* ∗ x,y,z coordinates: 50.0,0.0,20.6
	* ∗ 3d normalized orientation vector. In range [-1,1] for each x,y,z axis: 0.0,0.0,1.0
	* ∗ the cylinder diameter: 14.2
	* ∗ the cylinder height: 21.42
	* ∗ R,G,B colors in range [0,255]: 10, 0, 255
 */
//bool	cylinder_intersection(t_minirt *rt, t_ray *ray)
//{
//	double r = rt->Cylinder->diameter / 2;
//	double a = powf(ray.dir.x, 2.0) + powf(ray.dir.z, 2.0);
//	double b = 2.0 * ray.origin.x * ray.dir.x + 2.0 * ray.origin.z * ray.dir.z;
//	double c = powf(ray.origin.x, 2.0) + powf(ray.origin.z, 2) - r; // they put 1 i don't know why
//	double disc = powf(b, 2) - 4 * a * c;
//	// ? if the disc is equals to 0  the ray does not intersect with the cylinder
//	if (disc < EPSILON)
//		return false;
//	return true;
//}

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

	t = FLT_MAX;
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
t_color convet(int *c)
{
	t_color re;

	re.r = c[0];
	re.g = c[1];
	re.b = c[2];
	return re;
}
bool	cylinder_intersection(t_minirt *rt, t_ray ray, double *t, t_hit *hit)
{
	int i = -1;
	double t_min;
	double M;

	t_point A;
	t_point B;
	t_point hHat;

	*t = FLT_MAX;
	t_min = FLT_MAX;
	t_Cylinder *cy=  rt->Cylinder;
	ray.direction = normalizing(ray.direction);
	while (++i < rt->Data->shape.cy)
	{
		A = v_mul(cy[i].height, cy[i].orientation); //to find orign of top
		B = normalizing(A); //to find direction of top
		cy[i].top = v_adding(v_mul(cy[i].height, B), cy[i].cordinates); //find top point
		cy[i].X = v_sub(ray.origin, cy[i].top);
		hHat = normalizing(v_sub(cy[i].top, v_adding(cy[i].top, v_mul(cy[i].height, cy[i].orientation))));
		cy[i].Q.a = v_dot(ray.direction, ray.direction) - pow(v_dot(ray.direction, hHat), 2);
		cy[i].Q.b = 2 * (v_dot(ray.direction, cy[i].X) - (v_dot(ray.direction, hHat) * v_dot(cy[i].X, hHat)));
		cy[i].Q.c = v_dot(cy[i].X, cy[i].X) - pow(v_dot(cy[i].X, hHat), 2) - pow(cy[i].redius, 2);
		cy[i].Q.discriminant = pow(cy[i].Q.b, 2) - (4 * cy[i].Q.a * cy[i].Q.c);
		if (cy[i].Q.discriminant < EPSILON)
			continue ;
		cy[i].Q.sqrt_disc = sqrt(cy[i].Q.discriminant);
		t_min = git_root(cy[i], hHat, ray, &M);
		if (t_min < *t)
		{
			*t= t_min;
			hit->obj_color = convet((int *)cy[i].color);
			hit->hit_pos = v_adding(cy[i].top, v_mul(M, hHat));
			hit->normal = normalizing(v_sub(hit->hit_pos, v_sub(cy[i].top, v_mul(M, hHat))));
			if (rt->Mlx->mouse)
				rt->Mlx->obj.index = i;
		}
	}
	if (*t == FLT_MAX)
		return false;
	return true;
}
