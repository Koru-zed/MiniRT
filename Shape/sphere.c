#include "../Include/miniRT.h"

double	get_root(double sqrt_disc, double b, double a)
{
	double	t1;
	double	t2;
	double	t;
	double	min;
	double	max;

	t1 = (-b + sqrt_disc) / (2 * a);
	t2 = (-b - sqrt_disc) / (2 * a);
	min = fmin(t1, t2);
	max = fmax(t1, t2);
	if (min >= EPSILON)
		t = min;
	else
		t = max;
	return (t);
}

t_hit	*get_hit_data(t_ray r, double hdest, t_hit *p_hit, t_Sphere sphere)
{
	(p_hit)->hit_pos = v_adding(r.origin, v_mul(hdest, r.direction));
	(p_hit)->obj_color = add_color(sphere.color);
	(p_hit)->normal = normalizing(v_sub((p_hit)->hit_pos, sphere.center));
	return (p_hit);
}

void	intersect_sp(t_minirt *rt, t_ray r, t_quadratic qd, t_hit *p_hit)
{
	double		t_min;
	t_point		dist;
	t_Sphere	*s;
	int			i;

	i = -1;
	s = rt->sphere;
	while (++i < rt->data->shape.sp)
	{
		dist = v_sub(r.origin, s[i].center);
		qd.b = 2 * v_dot(r.direction, dist);
		qd.c = v_dot(dist, dist) - (s[i].radius * s[i].radius);
		qd.discriminant = pow(qd.b, 2) - (4 * qd.a * qd.c);
		if (qd.discriminant < EPSILON)
			continue ;
		qd.sqrt_disc = sqrt(qd.discriminant);
		t_min = get_root(qd.sqrt_disc, qd.b, qd.a);
		if (t_min < p_hit->hdest)
		{
			p_hit->hdest = t_min;
			p_hit = get_hit_data(r, p_hit->hdest, p_hit, s[i]);
			if (rt->mlx->mouse)
				rt->mlx->obj.index = i;
		}
	}
}

bool	intersect_r_sphere(t_ray r, t_minirt *rt, double *t, t_hit *p_hit)
{
	t_Sphere	*s;
	t_quadratic	qd;

	r.direction = normalizing(r.direction);
	qd.a = v_dot(r.direction, r.direction);
	p_hit->hdest = FLT_MAX;
	intersect_sp(rt, r, qd, p_hit);
	if (p_hit->hdest == FLT_MAX)
		return (false);
	*t = p_hit->hdest;
	return (true);
}
