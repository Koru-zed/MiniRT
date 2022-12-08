/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-jao <mait-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:05:02 by mait-jao          #+#    #+#             */
/*   Updated: 2022/12/08 18:29:01 by mait-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/miniRT.h"

t_point	new_point(double x, double y, double z)
{
	t_point	pos;

	pos.x = x;
	pos.y = y;
	pos.z = z;
	return (pos);
}

t_color	add_color(const size_t *c)
{
	t_color	obj;

	obj.r = (int)c[0];
	obj.g = (int)c[1];
	obj.b = (int)c[2];
	return (obj);
}

void	name_obj(t_minirt *rt)
{
	if (rt->mlx->obj.object == _PLANE)
		ft_putstr_fd("Plane selected\n", 2);
	else if (rt->mlx->obj.object == _SEPHER)
		ft_putstr_fd("Sepher selected\n", 2);
	else if (rt->mlx->obj.object == _CYLINDER)
		ft_putstr_fd("Cylinder selected\n", 2);
}
