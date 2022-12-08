/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-jao <mait-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:03:36 by mait-jao          #+#    #+#             */
/*   Updated: 2022/12/08 18:22:40 by mait-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/miniRT.h"

void	scroll_up(t_minirt *mini)
{
	int	i;

	mini->mlx->_do = 1;
	i = mini->mlx->obj.index;
	if (!mini->mlx->obj.object && mini->camera->fov > 0)
		mini->camera->fov -= 5;
	else if (mini->mlx->obj.object == _SEPHER && \
		(mini->sphere[i].radius - 0.5) > EPSILON)
		mini->sphere[i].radius -= 0.5;
	else if (mini->mlx->obj.object == _CYLINDER && \
		(mini->cylinder[i].redius - 0.5) >= EPSILON && \
			(mini->cylinder[i].height - 1) >= EPSILON)
	{
		mini->cylinder[i].redius -= 0.5;
		mini->cylinder[i].height -= 1;
	}
}

void	scroll_down(t_minirt *mini)
{
	int	i;

	mini->mlx->_do = 1;
	i = mini->mlx->obj.index;
	if (!mini->mlx->obj.object && mini->camera->fov <= 170)
		mini->camera->fov += 5;
	else if (mini->mlx->obj.object == _SEPHER)
		mini->sphere[i].radius += 0.5;
	else if (mini->mlx->obj.object == _CYLINDER)
	{
		mini->cylinder[i].redius += 0.5;
		mini->cylinder[i].height += 1;
	}
}

int	ft_mouse(int scroll, int x, int y, t_minirt *mini)
{
	int	i;

	mini->mlx->_do = 0;
	i = mini->mlx->obj.index;
	if (scroll == 1)
	{
		mini->mlx->mouse = 1;
		mini->mlx->rotate = 0;
		intersection_over_objects(mini, ray_generator(mini, x, y));
		mini->mlx->mouse = 0;
	}
	else if (scroll == 4)
		scroll_up(mini);
	else if (scroll == 5)
		scroll_down(mini);
	if (mini->mlx->_do)
	{
		mlx_clear_window(mini->mlx->_mlx, mini->mlx->win);
		ray_render(mini);
	}
	return (0);
}

void	edit_mini(t_minirt *mini, int key)
{
	if (!mini->mlx->obj.object)
		edit_camera(mini, key);
	else if (mini->mlx->obj.object == _SEPHER)
		edit_sphere(mini, key);
	else if (mini->mlx->obj.object == _PLANE)
		edit_plane(mini, key);
	else if (mini->mlx->obj.object == _CYLINDER)
		edit_cylinder(mini, key);
	else if (mini->mlx->obj.object == _LIGHT)
		edit_light(mini, key);
	if (mini->mlx->_do)
	{
		mlx_clear_window(mini->mlx->_mlx, mini->mlx->win);
		ray_render(mini);
	}
}

int	press_key(int key, t_minirt *mini)
{
	if (key == KEYUP)
		edit_mini(mini, key);
	else if (key == KEYDOWN)
		edit_mini(mini, key);
	else if (key == KEYLEFT)
		edit_mini(mini, key);
	else if (key == KEYRIGHT)
		edit_mini(mini, key);
	else if (key == _LIGHT)
	{
		mini->mlx->obj.object = _LIGHT;
		ft_putstr_fd("Light selected\n", 2);
	}
	else if (key == DESTROY)
		free_mini(mini);
	else if (key == ZERO)
	{
		mini->mlx->obj.object = 0;
		mini->mlx->obj.index = 0;
		mini->mlx->rotate = 0;
		mini->mlx->_do = -1;
	}
	rotation_key(key, mini);
	return (0);
}
