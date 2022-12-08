#include "../Include/miniRT.h"

void	print_point(t_point p)
{
	printf("p.x = [%f] | ", p.x);
	printf("p.y = [%f] | ", p.y);
	printf("p.z = [%f]\n", p.z);
	printf("************************************************\n");
}

void	ft_swap(double *x, double *y)
{
	double	z;

	z = *x;
	*x = *y;
	*y = z;
}

double	git_root(t_Cylinder cy, t_ray ray, double *m)
{
	double	t;
	double	t1;
	double	m1;
	double m2;
	double	t2;

	t = FLT_MAX;
	t1 = (-cy.q.b + cy.q.sqrt_disc) / (2 * cy.q.a);
	t2 = (-cy.q.b - cy.q.sqrt_disc) / (2 * cy.q.a);
	if (t1 > t2)
		ft_swap(&t1, &t2);
	m1 = (v_dot(ray.direction, v_mul(t1, cy.ray.direction))) \
		+ v_dot(cy.x, cy.ray.direction);
	m2 = (v_dot(ray.direction, v_mul(t2, cy.ray.direction))) \
		+ v_dot(cy.x, cy.ray.direction);
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

t_color	convet(size_t *c)
{
	t_color	re;

	re.r = (int)c[0];
	re.g = (int)c[1];
	re.b = (int)c[2];
	return (re);
}

void	calc_discrement(t_Cylinder *cy, t_ray ray)
{
	cy->x = v_sub(ray.origin, cy->ray.origin);
	cy->q.a = v_dot(ray.direction, ray.direction) - pow(v_dot(ray.direction, cy->ray.direction), 2);
	cy->q.b = 2 * (v_dot(ray.direction, cy->x) \
		- (v_dot(ray.direction, cy->ray.direction) \
			* v_dot(cy->x, cy->ray.direction)));
	cy->q.c = v_dot(cy->x, cy->x) - pow(v_dot(cy->x, cy->ray.direction), 2) - pow(cy->redius, 2);
	cy->q.discriminant = pow(cy->q.b, 2) - (4 * cy->q.a * cy->q.c);
	cy->q.sqrt_disc = sqrt(cy->q.discriminant);
}

bool	cylinder_intersection(t_minirt *rt, t_ray ray, double *t, t_hit *hit)
{
	int i = -1;
	double t_min;
	double M;

	*t = FLT_MAX;
	t_min = FLT_MAX;
	t_Cylinder *cy=  rt->cylinder;
	ray.direction = normalizing(ray.direction);
	while (++i < rt->data->shape.cy)
	{
		calc_discrement(&cy[i], ray);
		if (cy[i].q.discriminant < EPSILON)
			continue ;
		t_min = git_root(cy[i], ray, &M);
		if (t_min < *t)
		{
			*t= t_min;
			hit->obj_color = convet(cy[i].color);
			hit->hit_pos = v_adding(ray.origin, v_mul(*t, ray.direction));
			hit->normal = normalizing(v_sub(v_sub(hit->hit_pos, cy[i].ray.origin), v_mul(M, cy[i].ray.direction)));
			if (rt->mlx->mouse)
				rt->mlx->obj.index = i;
		}
	}
	if (*t == FLT_MAX)
		return false;
	return true;
}