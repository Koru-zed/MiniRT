/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-jao <mait-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:03:38 by mait-jao          #+#    #+#             */
/*   Updated: 2022/12/08 16:03:39 by mait-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/miniRT.h"

void	edit_light(t_minirt *mini, int key)
{
	mini->mlx->_do = 1;
	if (key == KEYUP)
		mini->light->cordinates.y += 0.75;
	else if (key == KEYDOWN)
		mini->light->cordinates.y -= 0.75;
	else if (key == KEYLEFT)
		mini->light->cordinates.x += 0.75;
	else if (key == KEYRIGHT)
		mini->light->cordinates.x -= 0.75;
	else
		mini->mlx->_do = 0;
}

void	edit_sphere(t_minirt *mini, int key)
{
	mini->mlx->_do = 1;
	if (key == KEYUP)
		mini->sphere[mini->mlx->obj.index].center.y += 0.75;
	else if (key == KEYDOWN)
		mini->sphere[mini->mlx->obj.index].center.y -= 0.75;
	else if (key == KEYLEFT)
		mini->sphere[mini->mlx->obj.index].center.x += 0.75;
	else if (key == KEYRIGHT)
		mini->sphere[mini->mlx->obj.index].center.x -= 0.75;
	else
		mini->mlx->_do = 0;
}

void	edit_plane(t_minirt *mini, int key)
{
	mini->mlx->_do = 1;
	if (mini->mlx->rotate)
		rotation_plane(mini, key);
	else if (key == KEYUP)
		mini->plane[mini->mlx->obj.index].ray.origin.y += 0.75;
	else if (key == KEYDOWN)
		mini->plane[mini->mlx->obj.index].ray.origin.y -= 0.75;
	else if (key == KEYLEFT)
		mini->plane[mini->mlx->obj.index].ray.origin.x += 0.75;
	else if (key == KEYRIGHT)
		mini->plane[mini->mlx->obj.index].ray.origin.x -= 0.75;
	else
		mini->mlx->_do = 0;
}

void	edit_cylinder(t_minirt *mini, int key)
{
	mini->mlx->_do = 1;
	if (mini->mlx->rotate)
		rotation_cylinder(mini, key);
	else if (key == KEYUP)
		mini->cylinder[mini->mlx->obj.index].ray.origin.y += 0.75;
	else if (key == KEYDOWN)
		mini->cylinder[mini->mlx->obj.index].ray.origin.y -= 0.75;
	else if (key == KEYLEFT)
		mini->cylinder[mini->mlx->obj.index].ray.origin.x += 0.75;
	else if (key == KEYRIGHT)
		mini->cylinder[mini->mlx->obj.index].ray.origin.x -= 0.75;
	else
		mini->mlx->_do = 0;
}

void	edit_camera(t_minirt *mini, int key)
{
	t_matrix	matrix;

	mini->mlx->_do = 1;
	matrix = mini->camera->matrix;
	if (!mini->mlx->rotate)
	{
		if (key == KEYUP)
			mini->camera->ray.origin.y -= 0.5;
		else if (key == KEYDOWN)
			mini->camera->ray.origin.y += 0.5;
		else if (key == KEYLEFT)
			mini->camera->ray.origin.x -= 0.5;
		else if (key == KEYRIGHT)
			mini->camera->ray.origin.x += 0.5;
	}
	else if (mini->mlx->rotate)
		rotate_camera(mini, key);
	else
		mini->mlx->_do = 0;
}
