/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <ael-mous@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 16:56:55 by ael-mous          #+#    #+#             */
/*   Updated: 2022/12/08 22:40:24 by ael-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/miniRT.h"

void	update_data(double *t, t_hit *p_hit, t_Plane plane, t_ray ray)
{
	(p_hit)->obj_color = add_color(plane.color);
	(p_hit)->hit_pos = v_adding(ray.origin, v_mul(*t, ray.direction));
	(p_hit)->normal = plane.ray.direction;
}

double	find_t(t_ray ray, t_Plane *plane, int i)
{
	double	p;
	double	tmin;
	t_point	res;

	p = v_dot(plane[i].ray.direction, ray.direction);
	res = v_sub(plane[i].ray.origin, ray.origin);
	tmin = v_dot(res, plane[i].ray.direction) / p;
	return (tmin);
}

bool	intersect_plane(t_minirt *rt, t_ray ray, double *t, t_hit *p_hit)
{
	int		i;
	double	tmin;
	t_Plane	*plane;

	i = -1;
	plane = rt->plane;
	*t = FLT_MAX;
	ray.direction = normalizing(ray.direction);
	while (++i < rt->data->shape.pl)
	{
		tmin = find_t(ray, plane, i);
		if (tmin > EPSILON)
		{
			if (*t > tmin)
			{
				*t = tmin;
				update_data(t, p_hit, plane[i], ray);
				if (rt->mlx->mouse)
					rt->mlx->obj.index = i;
			}
		}
	}
	if (*t == FLT_MAX)
		return (false);
	return (true);
}
