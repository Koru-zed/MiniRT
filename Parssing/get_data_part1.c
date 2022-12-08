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
				ft_putstr_fd("Error : out of range [0.0;1.0]", 1);
			free_mini(mini);
			exit(EXIT_FAILURE);
		}
		set_color(data->pars[2], mini->ambient->color, mini);
		return (1);
	}
	ft_putstr_fd("Munltiple Ambient", 1);
	free_mini(mini);
	exit(EXIT_FAILURE);
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
		mini->camera->fov = ft_atoi(data->pars[3]);
		if (mini->check || mini->camera->fov > 180)
		{
			ft_putstr_fd("Error : out of range [0;180]", 1);
			free_mini(mini);
			exit(EXIT_FAILURE);
		}
		return (1);
	}
	ft_putstr_fd("Munltiple Camera", 1);
	free_mini(mini);
	exit(EXIT_FAILURE);
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
				ft_putstr_fd("Error : out of range [0.0;1.0]", 1);
			free_mini(mini);
			exit(EXIT_FAILURE);
		}
		return (1);
	}
	ft_putstr_fd("Munltiple Light", 1);
	free_mini(mini);
	exit(EXIT_FAILURE);
}
