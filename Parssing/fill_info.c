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
	mini->Ambient = ft_calloc(mini->Data->shape.A, sizeof(t_Ambient));
	mini->Camera = ft_calloc(mini->Data->shape.C, sizeof(t_Camera));
	mini->Light = ft_calloc(mini->Data->shape.L, sizeof(t_Light));
	mini->Sphere = ft_calloc(mini->Data->shape.sp, sizeof(t_Sphere));
	mini->Plane = ft_calloc(mini->Data->shape.pl, sizeof(t_Plane));
	mini->Cylinder = ft_calloc(mini->Data->shape.cy, sizeof(t_Cylinder));
}

void	fill_info(t_minirt *mini)
{
	t_data	*_data;

	_data = mini->Data;
	alloc_mini(mini);
	while (_data && _data->info)
	{
		if (!check_data(mini, _data))
		{
			free_mini(mini);
			ft_putstr_fd("Error : Data not valid\n", 1);
			exit(EXIT_FAILURE);
		}
		_data = _data->next;
	}
}
