# include "../Include/miniRT.h"

void free_Sphere(t_Sphere *_Sphere)
{
    int i;

    i = -1;
    while (_Sphere[++i])
        free(_Sphere[i]);
    free(_Sphere);
}

void free_Plane(t_Plane *_Plane)
{
    int i;

    i = -1;
    while (_Plane[++i])
        free(_Plane[i]);
    free(_Plane);
}

void free_Cylinder(t_Cylinder *_Cylinder)
{
    int i;

    i = -1;
    while (_Cylinder[++i])
        free(_Cylinder[i]);
    free(_Cylinder);
}

void free_data(t_data *_data)
{
    t_data *next_data;

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

void    free_mini(t_minirt *mini)
{
    if (mini->Ambient)
        free(mini->Ambient);
    if (mini->Camera)
        free(mini->Camera);
    if (mini->Light)
        free(mini->Light);
    free_Sphere(mini->Sphere);
    free_Plane(mini->Plane);
    free_Cylinder(mini->Cylinder);
    free_data(mini->Data);
    free(mini);
}
