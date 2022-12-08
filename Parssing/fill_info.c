/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-jao <mait-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:02:54 by mait-jao          #+#    #+#             */
/*   Updated: 2022/12/08 18:28:38 by mait-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/miniRT.h"

size_t	check_data(t_minirt *mini, t_data *data)
{
	if (!ft_strcmp(data->pars[0], AMBIENT))
		get_ambient_lightning(mini, data);
	else if (!ft_strcmp(data->pars[0], CAMERA))
		get_camera(mini, data);
	else if (!ft_strcmp(data->pars[0], LIGHT))
		get_light(mini, data);
	else if (!ft_strcmp(data->pars[0], SEPHER))
		get_sphere(mini, data);
	else if (!ft_strcmp(data->pars[0], PLANE))
		get_plane(mini, data);
	else if (!ft_strcmp(data->pars[0], CYLINDER))
		get_cylinder(mini, data);
	else if (ft_strcmp(data->pars[0], "#"))
		return (0);
	return (1);
}

void	alloc_mini(t_minirt *mini)
{
	mini->ambient = ft_calloc(mini->data->shape.a, sizeof(t_Ambient));
	mini->camera = ft_calloc(mini->data->shape.c, sizeof(t_Camera));
	mini->light = ft_calloc(mini->data->shape.l, sizeof(t_Light));
	mini->sphere = ft_calloc(mini->data->shape.sp, sizeof(t_Sphere));
	mini->plane = ft_calloc(mini->data->shape.pl, sizeof(t_Plane));
	mini->cylinder = ft_calloc(mini->data->shape.cy, sizeof(t_Cylinder));
}

void	fill_info(t_minirt *mini)
{
	t_data	*_data;

	_data = mini->data;
	alloc_mini(mini);
	while (_data && _data->info)
	{
		if (!check_data(mini, _data))
		{
			ft_putstr_fd("Error : Data not valid\n", 1);
			free_mini(mini);
		}
		_data = _data->next;
	}
}
