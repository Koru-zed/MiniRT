/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 16:56:55 by ael-mous          #+#    #+#             */
/*   Updated: 2022/12/07 16:57:04 by ael-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/miniRT.h"

/*
 ?  for the plane configuration :
 * ∗ x,y,z coordinates: 0.0, 0.0, -10.0
 *		∗ 3d normalized orientation vector. In range [-1,1] for each x,y,z axis:
 *		0.0, 0.0, 1.0
 *		∗ R,G,B colors in range [0-255]: 0, 0, 255
 */
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
	plane = rt->Plane;
	*t = FLT_MAX;
	ray.direction = normalizing(ray.direction);
	while (++i < rt->Data->shape.pl)
	{
		tmin = find_t(ray, plane, i);
		if (tmin > EPSILON)
		{
			if (*t > tmin)
			{
				*t = tmin;
				update_data(t, p_hit, plane[i], ray);
				if (rt->Mlx->mouse)
					rt->Mlx->obj.index = i;
			}
		}
	}
	if (*t == FLT_MAX)
		return (false);
	return (true);
}
