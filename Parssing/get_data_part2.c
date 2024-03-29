/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data_part2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-jao <mait-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:03:10 by mait-jao          #+#    #+#             */
/*   Updated: 2022/12/08 22:10:05 by mait-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/miniRT.h"

int	get_plane(t_minirt *mini, t_data *data)
{
	static int	i;

	if (ft_arrylen(data->pars) != 4)
	{
		mini->check = -1;
		return (-1);
	}
	set_cordinates(data->pars[1], &mini->plane[i].ray.origin, mini);
	set_orientation(data->pars[2], &mini->plane[i].ray.direction, mini);
	set_color(data->pars[3], mini->plane[i].color, mini);
	i++;
	return (1);
}

int	get_sphere(t_minirt *mini, t_data *data)
{
	static int	i;

	if (ft_arrylen(data->pars) != 4)
	{
		mini->check = -1;
		return (-1);
	}
	set_cordinates(data->pars[1], &mini->sphere[i].center, mini);
	mini->sphere[i].radius = ft_atod(data->pars[2], &mini->check) / 2;
	if (mini->check)
		free_mini(mini);
	set_color(data->pars[3], mini->sphere[i].color, mini);
	i++;
	return (1);
}

int	get_cylinder(t_minirt *mini, t_data *data)
{
	static int	i;

	if (ft_arrylen(data->pars) != 6)
	{
		mini->check = -1;
		return (-1);
	}
	set_cordinates(data->pars[1], &mini->cylinder[i].ray.origin, mini);
	set_orientation(data->pars[2], &mini->cylinder[i].ray.direction, mini);
	mini->cylinder[i].redius = ft_atod(data->pars[3], &mini->check) / 2;
	mini->cylinder[i].height = ft_atod(data->pars[4], &mini->check);
	if (mini->check)
		free_mini(mini);
	set_color(data->pars[5], mini->cylinder[i].color, mini);
	i++;
	return (1);
}
