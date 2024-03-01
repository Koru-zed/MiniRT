/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-jao <mait-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:03:42 by mait-jao          #+#    #+#             */
/*   Updated: 2022/12/08 16:03:43 by mait-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/miniRT.h"

t_matrix	new_matrix(t_point r, t_point up, t_point forwd, t_point org)
{
	t_matrix	new;

	new.m[0][0] = r.x;
	new.m[0][1] = r.y;
	new.m[0][2] = r.z;
	new.m[0][3] = 0;
	new.m[1][0] = up.x;
	new.m[1][1] = up.y;
	new.m[1][2] = up.z;
	new.m[1][3] = 0;
	new.m[2][0] = forwd.x;
	new.m[2][1] = forwd.y;
	new.m[2][2] = forwd.z;
	new.m[2][3] = 0;
	new.m[3][0] = org.x;
	new.m[3][1] = org.y;
	new.m[3][2] = org.z;
	new.m[3][3] = 1;
	return (new);
}

t_matrix	dir_matrix(void)
{
	t_point	forward;
	t_point	origin;
	t_point	right;
	t_point	up;

	right = new_point(1, 0, 0);
	up = new_point(0, 1, 0);
	forward = new_point(0, 0, 1);
	origin = new_point(0, 0, 0);
	return (new_matrix(right, up, forward, origin));
}

void	camera_matrix(t_View *_view)
{
	t_point	right;
	t_point	up;

	right = normalizing(v_cross(new_point(0, 1, 0), _view->ray.direction));
	up = normalizing(v_cross(_view->ray.direction, right));
	_view->matrix = new_matrix(right, up, \
		_view->ray.direction, _view->ray.origin);
}
