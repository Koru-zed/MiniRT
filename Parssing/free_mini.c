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
	free_data(mini->data);
	free(mini);
	exit(EXIT_SUCCESS);
}
