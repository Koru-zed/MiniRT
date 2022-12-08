/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data_part1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-jao <mait-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:03:07 by mait-jao          #+#    #+#             */
/*   Updated: 2022/12/08 22:08:45 by mait-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/miniRT.h"

int	get_ambient_lightning(t_minirt *mini, t_data *data)
{
	if (!mini->ambient->repetition)
	{
		mini->ambient->repetition = 1;
		if (ft_arrylen(data->pars) != 3)
		{
			mini->check = -1;
			return (-1);
		}
		mini->ambient->ratio = ft_atod(data->pars[1], &mini->check);
		if (mini->check == -1
			|| !(mini->ambient->ratio >= 0.0f && mini->ambient->ratio <= 1.0f))
		{
			if (mini->check != -1)
				ft_putstr_fd("\033[1;91mError\nout of range [0.0;1.0]", 1);
			free_mini(mini);
		}
		set_color(data->pars[2], mini->ambient->color, mini);
		return (1);
	}
	ft_putstr_fd("\033[1;91mError\nMunltiple Ambient", 1);
	free_mini(mini);
	return (-1);
}

int	get_camera(t_minirt *mini, t_data *data)
{
	if (!mini->camera->repetition)
	{
		mini->camera->repetition = 1;
		if (ft_arrylen(data->pars) != 4)
		{
			mini->check = -1;
			return (-1);
		}
		set_cordinates(data->pars[1], &mini->camera->ray.origin, mini);
		set_orientation(data->pars[2], &mini->camera->ray.direction, mini);
		mini->camera->fov = ft_my_atoi(data->pars[3], &mini->check);
		if (mini->check == -1 || mini->camera->fov > 180)
		{
			ft_putstr_fd("\033[1;91mError\nout of range [0;180]", 1);
			free_mini(mini);
		}
		return (1);
	}
	ft_putstr_fd("\033[1;91mError\nMunltiple Camera", 1);
	free_mini(mini);
	return (-1);
}

int	get_light(t_minirt *mini, t_data *data)
{
	if (!mini->light->repetition)
	{
		mini->light->repetition = 1;
		if (ft_arrylen(data->pars) != 3)
		{
			mini->check = -1;
			return (-1);
		}
		set_cordinates(data->pars[1], &mini->light->cordinates, mini);
		mini->light->brightenss = ft_atod(data->pars[2], &mini->check);
		if (mini->check || (mini->light->brightenss < 0.0f
				&& mini->light->brightenss > 1.0f))
		{
			if (mini->check != -1)
				ft_putstr_fd("\033[1;91mError\nout of range [0.0;1.0]", 1);
			free_mini(mini);
		}
		return (1);
	}
	ft_putstr_fd("\033[1;91mError\nMunltiple Light", 1);
	free_mini(mini);
	return (-1);
}
