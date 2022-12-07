#include "../Include/miniRT.h"

void	checker_valid_data(t_data *data, t_num_shape *_shape)
{
	if (!ft_strcmp(data->pars[0], AMBIENT))
		_shape->A++;
	else if (!ft_strcmp(data->pars[0], CAMERA))
		_shape->C++;
	else if (!ft_strcmp(data->pars[0], LIGHT))
		_shape->L++;
	else if (!ft_strcmp(data->pars[0], SEPHER))
		_shape->sp++;
	else if (!ft_strcmp(data->pars[0], PLANE))
		_shape->pl++;
	else if (!ft_strcmp(data->pars[0], CYLINDER))
		_shape->cy++;
	else if (ft_strcmp(data->pars[0], "#"))
	{
		printf("{%s}\n", data->pars[0]);
		ft_putstr_fd("Error : Data not valid\n", 1);
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
	n_data->check_empty = ft_check_valid(get_next_line(fd), n_data, n_shape);
	if (n_data->check_empty == -1)
		return ;
	if (n_data->info)
	{
		n_data->next = ft_calloc(1, sizeof(t_data));
		fill_data(n_data->next, n_shape, fd);
		return ;
	}
	else
		fill_data(n_data, n_shape, fd);
}
