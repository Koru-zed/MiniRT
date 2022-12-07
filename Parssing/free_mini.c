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
	if (mini->Ambient)
		free(mini->Ambient);
	if (mini->Camera)
		free(mini->Camera);
	if (mini->Light)
		free(mini->Light);
	if (mini->Sphere)
		free(mini->Sphere);
	if (mini->Plane)
		free(mini->Plane);
	if (mini->Cylinder)
		free(mini->Cylinder);
	free_data(mini->Data);
	free(mini);
	exit(EXIT_SUCCESS);
}
