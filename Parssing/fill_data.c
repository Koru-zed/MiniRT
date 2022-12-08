/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-jao <mait-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:02:51 by mait-jao          #+#    #+#             */
/*   Updated: 2022/12/08 21:04:56 by mait-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/miniRT.h"

void	checker_valid_data(t_data *data, t_num_shape *_shape)
{
	if (!ft_strcmp(data->pars[0], AMBIENT))
		_shape->a++;
	else if (!ft_strcmp(data->pars[0], CAMERA))
		_shape->c++;
	else if (!ft_strcmp(data->pars[0], LIGHT))
		_shape->l++;
	else if (!ft_strcmp(data->pars[0], SEPHER))
		_shape->sp++;
	else if (!ft_strcmp(data->pars[0], PLANE))
		_shape->pl++;
	else if (!ft_strcmp(data->pars[0], CYLINDER))
		_shape->cy++;
	else if (ft_strcmp(data->pars[0], "#"))
	{
		printf("\033[1;97m{\033[1;93m%s\033[1;97m}\n", data->pars[0]);
		ft_putstr_fd("\033[1;91mError\nData not valid\n", 1);
		free_data(data);
		exit(EXIT_FAILURE);
	}
}

int	ft_check_valid(char *filename, t_data *data, t_num_shape *_shape)
{
	int	i;

	i = 0;
	if (!filename)
		return (-1);
	while (filename[i] && (filename[i] == ' ' || filename[i] == '\t'))
		i++;
	if (filename[i] && filename[i] != '\n')
	{
		data->info = filename;
		data->pars = ft_split(data->info, ' ');
		checker_valid_data(data, _shape);
		return (1);
	}
	return (0);
}

void	fill_data(t_data *n_data, t_num_shape *n_shape, int fd)
{
	char	*s;

	s = get_next_line(fd);
	n_data->check_empty = ft_check_valid(s, n_data, n_shape);
	if (!n_data || n_data->check_empty == -1)
		return ;
	if (n_data->info)
	{
		n_data->next = ft_calloc(1, sizeof(t_data));
		fill_data(n_data->next, n_shape, fd);
		free(s);
		return ;
	}
	else
	{
		fill_data(n_data, n_shape, fd);
		free(s);
	}
}
