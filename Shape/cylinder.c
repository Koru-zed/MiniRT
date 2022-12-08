#include "../Include/miniRT.h"

double	git_root(t_Cylinder cy, t_ray ray, double *mm)
{
	double	tt;
	double	t[2];
	double	m[2];

	tt = FLT_MAX;
	t[0] = (-cy.q.b + cy.q.sqrt_disc) / (2 * cy.q.a);
	t[1] = (-cy.q.b - cy.q.sqrt_disc) / (2 * cy.q.a);
	if (t[0] > t[1])
		ft_swap_double(&t[0], &t[1]);
	m[0] = (v_dot(ray.direction, v_mul(t[0], cy.ray.direction))) \
		+ v_dot(cy.x, cy.ray.direction);
	m[1] = (v_dot(ray.direction, v_mul(t[1], cy.ray.direction))) \
		+ v_dot(cy.x, cy.ray.direction);
	if (m[0] > EPSILON && m[0] <= cy.height)
	{
		tt = t[0];
		*mm = m[0];
	}
	else if (m[1] > EPSILON && m[1] <= cy.height)
	{
		tt = t[1];
		*mm = m[1];
	}
	return (tt);
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
	cy->q.a = v_dot(ray.direction, ray.direction) - \
		pow(v_dot(ray.direction, cy->ray.direction), 2);
	cy->q.b = 2 * (v_dot(ray.direction, cy->x) \
		- (v_dot(ray.direction, cy->ray.direction) \
			* v_dot(cy->x, cy->ray.direction)));
	cy->q.c = v_dot(cy->x, cy->x) - pow(v_dot(cy->x, cy->ray.direction), 2) \
		- pow(cy->redius, 2);
	cy->q.discriminant = pow(cy->q.b, 2) - (4 * cy->q.a * cy->q.c);
	cy->q.sqrt_disc = sqrt(cy->q.discriminant);
}

bool	get_hit(t_Cylinder cy, t_ray ray, t_hit *hit, double *t)
{
	int		i;
	double	max;
	double	t_min;

	t_min = FLT_MAX;
	t_min = git_root(cy, ray, &max);
	if (t_min < *t)
	{
		*t = t_min;
		hit->obj_color = convet(cy.color);
		hit->hit_pos = v_adding(ray.origin, v_mul(*t, ray.direction));
		hit->normal = normalizing(v_sub(v_sub(hit->hit_pos, \
		cy.ray.origin), v_mul(max, cy.ray.direction)));
		return (true);
	}
	return (false);
}

bool	cylinder_intersection(t_minirt *rt, t_ray ray, double *t, t_hit *hit)
{
	int		i;

	i = -1;
	*t = FLT_MAX;
	ray.direction = normalizing(ray.direction);
	while (++i < rt->data->shape.cy)
	{
		calc_discrement(&rt->cylinder[i], ray);
		if (rt->cylinder[i].q.discriminant < EPSILON)
			continue ;
		if (get_hit(rt->cylinder[i], ray, hit, t) && rt->mlx->mouse)
			rt->mlx->obj.index = i;
	}
	if (*t == FLT_MAX)
		return (false);
	return (true);
}
