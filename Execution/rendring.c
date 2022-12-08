/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendring.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-jao <mait-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:03:53 by mait-jao          #+#    #+#             */
/*   Updated: 2022/12/08 18:33:50 by mait-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/miniRT.h"

void	my_mlx_pixel_put(t_mlx *Mlx, int x, int y, int color)
{
	char	*dst;

	dst = Mlx->addr + (y * Mlx->line_length + x * (Mlx->bits_per_pixel >> 3));
	*(unsigned int *)dst = color;
}

void	iterate_over_objects(t_minirt *rt, t_ray ray, double *t, t_hit *hit)
{
	int		i;
	double	t_t[3];
	bool	is[3];
	t_hit	*p_hit;

	p_hit = malloc(sizeof(t_hit) * 3);
	i = -1;
	*t = DBL_MAX;
	t_t[0] = DBL_MAX;
	t_t[1] = DBL_MAX;
	t_t[2] = DBL_MAX;
	is[PL] = intersect_plane(rt, ray, &t_t[PL], &p_hit[PL]);
	is[SP] = intersect_r_sphere(ray, rt, &t_t[SP], &p_hit[SP]);
	is[CY] = cylinder_intersection(rt, ray, &t_t[CY], &p_hit[CY]);
	while (++i < 3)
	{
		if (is[i] && t_t[i] > EPSILON && t_t[i] < *t)
		{
			*t = t_t[i];
			*hit = p_hit[i];
		}
	}
	free(p_hit);
}

void	intescte_obj(t_minirt *rt, int i)
{
	if (i == PL)
		rt->mlx->obj.object = _PLANE;
	else if (i == SP)
		rt->mlx->obj.object = _SEPHER;
	else if (i == CY)
		rt->mlx->obj.object = _CYLINDER;
	else
		rt->mlx->obj.object = 0;
}

void	intersection_over_objects(t_minirt *rt, t_ray ray)
{
	int		i;
	double	t;
	double	t_t[3];
	t_hit	hit[3];
	bool	is[3];

	i = -1;
	t = DBL_MAX;
	t_t[0] = DBL_MAX;
	t_t[1] = DBL_MAX;
	t_t[2] = DBL_MAX;
	is[PL] = intersect_plane(rt, ray, &t_t[PL], &hit[PL]);
	is[SP] = intersect_r_sphere(ray, rt, &t_t[SP], &hit[SP]);
	is[CY] = cylinder_intersection(rt, ray, &t_t[CY], &hit[CY]);
	while (++i < 3)
	{
		if (is[i] && t_t[i] > EPSILON && t_t[i] < t)
		{
			t = t_t[i];
			intescte_obj(rt, i);
		}
	}
	name_obj(rt, t);
}

void	ray_render(t_minirt *mini)
{
	int		x;
	int		y;
	double	t;
	t_hit	*hit;
	t_ray	ray;

	y = -1;
	camera_matrix(mini->camera);
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			hit = ft_calloc(sizeof(t_hit), 1);
			ray = ray_generator(mini, x, y);
			iterate_over_objects(mini, ray, &t, hit);
			if (hit)
				my_mlx_pixel_put(mini->mlx, x, y, add_light(hit, mini));
			else
				my_mlx_pixel_put(mini->mlx, x, y, BLACK);
			free(hit);
		}
	}
	mlx_put_image_to_window(mini->mlx->_mlx, mini->mlx->win, \
		mini->mlx->img, 0, 0);
}
