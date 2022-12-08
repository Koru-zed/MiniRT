/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-jao <mait-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:03:55 by mait-jao          #+#    #+#             */
/*   Updated: 2022/12/08 16:06:16 by mait-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/miniRT.h"

void	rotation_cylinder(t_minirt *mini, int key)
{
	int		i;
	t_point	direction;

	i = mini->mlx->obj.index;
	direction = mini->cylinder[i].ray.direction;
	if (key == KEYLEFT && mini->mlx->rotate == ROTATE_X)
		direction = mul_point_matrix(direction, update_matrix_y(-3.6));
	else if (key == KEYRIGHT && mini->mlx->rotate == ROTATE_X)
		direction = mul_point_matrix(direction, update_matrix_y(3.6));
	else if (key == KEYUP && mini->mlx->rotate == ROTATE_Y)
		direction = mul_point_matrix(direction, update_matrix_x(3.6));
	else if (key == KEYDOWN && mini->mlx->rotate == ROTATE_Y)
		direction = mul_point_matrix(direction, update_matrix_x(-3.6));
}

void	rotation_plane(t_minirt *mini, int key)
{
	int		i;
	t_point	direction;

	i = mini->mlx->obj.index;
	direction = mini->plane[i].ray.direction;
	if (key == KEYLEFT && mini->mlx->rotate == ROTATE_X)
		direction = mul_point_matrix(direction, update_matrix_y(-3.6));
	else if (key == KEYRIGHT && mini->mlx->rotate == ROTATE_X)
		direction = mul_point_matrix(direction, update_matrix_y(3.86));
	else if (key == KEYUP && mini->mlx->rotate == ROTATE_Y)
		direction = mul_point_matrix(direction, update_matrix_x(3.6));
	else if (key == KEYDOWN && mini->mlx->rotate == ROTATE_Y)
		direction = mul_point_matrix(direction, update_matrix_x(-3.6));
}

void	rotate_camera(t_minirt *mini, int key)
{
	t_point	direction;

	direction = mini->camera->ray.direction;
	if (key == KEYLEFT && mini->mlx->rotate == ROTATE_X)
		direction = mul_point_matrix(direction, update_matrix_y(-3.6));
	else if (key == KEYRIGHT && mini->mlx->rotate == ROTATE_X)
		direction = mul_point_matrix(direction, update_matrix_y(3.6));
	else if (key == KEYUP && mini->mlx->rotate == ROTATE_Y && \
			direction.z > EPSILON)
		direction = mul_point_matrix(direction, update_matrix_x(-3.6));
	else if (key == KEYDOWN && mini->mlx->rotate == ROTATE_Y && \
			direction.z > EPSILON)
		direction = mul_point_matrix(direction, update_matrix_x(3.6));
	else if (key == KEYUP && mini->mlx->rotate == ROTATE_Y && \
			direction.z < EPSILON)
		direction = mul_point_matrix(direction, update_matrix_x(3.6));
	else if (key == KEYDOWN && mini->mlx->rotate == ROTATE_Y && \
			direction.z < EPSILON)
		direction = mul_point_matrix(direction, update_matrix_x(-3.6));
}

int	rotation_key(int key, t_minirt *mini)
{
	if (key == ROTATE_X)
		mini->mlx->rotate = ROTATE_X;
	else if (key == ROTATE_Y)
		mini->mlx->rotate = ROTATE_Y;
	else if (key == ROTATE_Z)
		mini->mlx->rotate = ROTATE_Z;
	return (0);
}
