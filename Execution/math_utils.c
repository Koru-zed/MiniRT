/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <ael-mous@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:03:47 by mait-jao          #+#    #+#             */
/*   Updated: 2022/12/08 22:39:52 by ael-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/miniRT.h"

t_point	normalizing(t_point p)
{
	double	mag;

	mag = length_squared(p);
	if (mag > 0)
	{
		p.x /= mag;
		p.y /= mag;
		p.z /= mag;
	}
	return (p);
}

t_matrix	cross_matrix(t_matrix m1, t_matrix m2)
{
	int			i;
	int			j;
	t_matrix	m12;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			m12.m[i][j] = m1.m[i][0] * m2.m[0][j] + \
					m1.m[i][1] * m2.m[1][j] + \
					m1.m[i][2] * m2.m[2][j] + \
					m1.m[i][3] * m2.m[3][j];
			j++;
		}
		i++;
	}
	return (m12);
}

t_point	mul_point_matrix(t_point p, t_matrix m)
{
	t_point	point;

	point.x = p.x * m.m[0][0] + p.y * m.m[1][0] + p.z * m.m[2][0] + m.m[3][0];
	point.y = p.x * m.m[0][1] + p.y * m.m[1][1] + p.z * m.m[2][1] + m.m[3][1];
	point.z = p.x * m.m[0][2] + p.y * m.m[1][2] + p.z * m.m[2][2] + m.m[3][2];
	return (point);
}

int	rgb(const t_color rgb)
{
	int	color;

	color = ((rgb.r << 16) + (rgb.g << 8) + rgb.b);
	return (color);
}

// magnitude
double	length_squared(t_point p)
{
	double	len;

	len = (p.x * p.x + p.y * p.y + p.z * p.z);
	return (sqrt(len));
}
