/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-jao <mait-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:03:05 by mait-jao          #+#    #+#             */
/*   Updated: 2022/12/08 21:04:29 by mait-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/miniRT.h"

void	ft_check_file(t_minirt *mini)
{
	int		i;
	char	*str;

	str = mini->file;
	i = ft_strlen(str);
	mini->check = -1;
	if (i > 3 && str[i - 1] == 't' && str[i - 2] == 'r' && str[i - 3] == '.')
	{
		mini->fd = open(str, O_RDONLY);
		if (mini->fd > 0)
			mini->check = 1;
	}
	if (mini->check == -1)
	{
		ft_putstr_fd("\033[1;91mError\nPath not valid", 2);
		exit(EXIT_FAILURE);
	}
	mini->check = 0;
}

void	free_data(t_data *_data)
{
	t_data	*next_data;

	next_data = NULL;
	while (_data && _data->pars)
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
