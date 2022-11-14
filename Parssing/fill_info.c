#include "../Include/miniRT.h"

size_t    check_data(t_minirt *mini, t_data *data)
{
	if (!ft_strcmp(data->pars[0], ambient))
		get_Ambient_lightning(mini, data);
	else if (!ft_strcmp(data->pars[0], camera))
		get_Camera(mini, data);
	else if (!ft_strcmp(data->pars[0], light))
		get_Light(mini, data);
	else if (!ft_strcmp(data->pars[0], sphre))
		get_Sphere(mini, data);
	else if (!ft_strcmp(data->pars[0], plane))
		get_Plane(mini, data);
	else if (!ft_strcmp(data->pars[0], cylinder))
		get_Cylinder(mini, data);
	else
		return (0);
	return 1;
}

void    fill_Info(t_minirt *mini)
{
    t_data *_data;

    _data = mini->Data;
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
