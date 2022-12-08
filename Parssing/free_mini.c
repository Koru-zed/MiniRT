/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-jao <mait-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:03:05 by mait-jao          #+#    #+#             */
/*   Updated: 2022/12/08 18:36:20 by mait-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/miniRT.h"

void	free_data(t_data *_data)
{
	t_data	*next_data;

	next_data = NULL;
	while (_data)
	{
		next_data = _data->next;
		if (_data->info)
			free(_data->info);
		if (_data->pars)
			ft_free_array(_data->pars);
		free(_data);
		_data = next_data;
	}
}

int	free_mini(t_minirt *mini)
{
	if (mini->ambient)
		free(mini->ambient);
	if (mini->camera)
		free(mini->camera);
	if (mini->light)
		free(mini->light);
	if (mini->sphere)
		free(mini->sphere);
	if (mini->plane)
		free(mini->plane);
	if (mini->cylinder)
		free(mini->cylinder);
	free(mini);
	exit(EXIT_SUCCESS);
}
