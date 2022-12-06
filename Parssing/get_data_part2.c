 #include "../Include/miniRT.h"

int    get_Plane(t_minirt *mini, t_data *data)
{
    static  int i;

    set_cordinates(data->pars[1], &mini->Plane[i].ray.origin, mini);
    set_orientation(data->pars[2], &mini->Plane[i].ray.direction, mini);
    set_color(data->pars[3], mini->Plane[i].color, mini);
    i++;
    return 1;
}

int    get_Sphere(t_minirt *mini, t_data *data)//**Spher
{
    static  int i;

    set_cordinates(data->pars[1], &mini->Sphere[i].center, mini);
    mini->Sphere[i].radius = ft_atod(data->pars[2], &mini->check) / 2;
    if (mini->check)
    {
        free_mini(mini);
        exit(EXIT_FAILURE);
    }
    set_color(data->pars[3], mini->Sphere[i].color, mini);
    i++;
    return 1;
}

int    get_Cylinder(t_minirt *mini, t_data *data)
{
    static  int i;

    set_cordinates(data->pars[1], &mini->Cylinder[i].ray.origin, mini);
    set_orientation(data->pars[2], &mini->Cylinder[i].ray.direction, mini);
    mini->Cylinder[i].redius = ft_atod(data->pars[3], &mini->check) / 2;
    mini->Cylinder[i].height = ft_atod(data->pars[4], &mini->check);
    if (mini->check)
    {
        free_mini(mini);
        exit(EXIT_FAILURE);
    }
    set_color(data->pars[5], mini->Cylinder[i].color, mini);
    i++;
    return 1;
}