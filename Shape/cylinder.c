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

double	git_root(t_Cylinder cy, t_ray ray, double *m)
{
	double t;
	double	t1;
	double	t2;

	t = FLT_MAX;
	t1 = (-cy.Q.b + cy.Q.sqrt_disc) / (2 * cy.Q.a);
	t2 = (-cy.Q.b - cy.Q.sqrt_disc) / (2 * cy.Q.a);
	if (t1 > t2)
		ft_swap(&t1, &t2);
	double m1 = (v_dot(ray.direction, v_mul(t1, cy.ray.direction))) + v_dot(cy.X, cy.ray.direction);
	double m2 = (v_dot(ray.direction, v_mul(t2, cy.ray.direction))) + v_dot(cy.X, cy.ray.direction);
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

void  calc_discrement(t_Cylinder *cy, t_ray ray)
{
	cy->X = v_sub(ray.origin, cy->ray.origin);
	cy->Q.a = v_dot(ray.direction, ray.direction) - pow(v_dot(ray.direction, cy->ray.direction), 2);
	cy->Q.b = 2 * (v_dot(ray.direction, cy->X) - (v_dot(ray.direction, cy->ray.direction) * v_dot(cy->X, cy->ray.direction)));
	cy->Q.c = v_dot(cy->X, cy->X) - pow(v_dot(cy->X, cy->ray.direction), 2) - pow(cy->redius, 2);
	cy->Q.discriminant = pow(cy->Q.b, 2) - (4 * cy->Q.a * cy->Q.c);
}

bool	cylinder_intersection(t_minirt *rt, t_ray ray, double *t, t_hit *hit)
{
	int i = -1;
	double t_min;
	double M;

	t_point A;
	t_point B;

	*t = FLT_MAX;
	t_min = FLT_MAX;
	t_Cylinder *cy=  rt->Cylinder;
	while (++i < rt->Data->shape.cy)
	{
		calc_discrement(&cy[i], ray);
		if (cy[i].Q.discriminant < EPSILON)
			continue ;
		cy[i].Q.sqrt_disc = sqrt(cy[i].Q.discriminant);
		t_min = git_root(cy[i], ray, &M);
		if (t_min < *t)
		{
			*t= t_min;
			hit->obj_color = convet(cy[i].color);
			hit->hit_pos = v_adding(cy[i].ray.origin, v_mul(M, cy[i].ray.direction));
			hit->normal = normalizing(v_sub(hit->hit_pos, v_sub(cy[i].ray.origin, v_mul(M, cy[i].ray.direction))));
			if (rt->Mlx->mouse)
				rt->Mlx->obj.index = i;
		}
	}
	if (*t == FLT_MAX)
		return false;
	return true;
}