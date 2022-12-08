/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <ael-mous@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:03:50 by mait-jao          #+#    #+#             */
/*   Updated: 2022/12/08 22:39:35 by ael-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/miniRT.h"

double	v_dot(const t_point u, const t_point v)
{
	return (u.x * v.x
		+ u.y * v.y
		+ u.z * v.z);
}

t_point	v_cross(const t_point u, const t_point v)
{
	t_point	vec;

	vec.x = u.y * v.z - u.z * v.y;
	vec.y = u.z * v.x - u.x * v.z;
	vec.z = u.x * v.y - u.y * v.x;
	return (vec);
}

t_point	v_mul(const double t, t_point p)
{
	t_point	a;

	a.x = p.x * t;
	a.y = p.y * t;
	a.z = p.z * t;
	return (a);
}

t_point	v_adding(t_point p, t_point v)
{
	t_point	a;

	a.x = p.x + v.x;
	a.y = p.y + v.y;
	a.z = p.z + v.z;
	return (a);
}

t_point	v_sub(t_point center, t_point origin)
{
	t_point	p;

	p.x = center.x - origin.x;
	p.y = center.y - origin.y;
	p.z = center.z - origin.z;
	return (p);
}
