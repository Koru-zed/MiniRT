# include "../Include/miniRT.h"

// void free_Sphere(t_Sphere *_Sphere)
// {
//     t_Sphere *tmp;

//     tmp = NULL;
//     while (_Sphere)
//     {
//         tmp = _Sphere->next;
//         free(_Sphere);
//         _Sphere = tmp;
//     }
// }

// void free_Plane(t_Plane *_Plane)
// {
//     t_Plane *tmp;

//     tmp = NULL;
//     while (_Plane)
//     {
//         tmp = _Plane->next;
//         free(_Plane);
//         _Plane = tmp;
//     }
// }

// void free_Cylinder(t_Cylinder *_Cylinder)
// {
//     t_Cylinder *tmp;

//     tmp = NULL;
//     while (_Cylinder)
//     {
//         tmp =_Cylinder->next;
//         free(_Cylinder);
//         _Cylinder = tmp;
//     }
// }

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
    // if (mini->Ambient)
    //     free(mini->Ambient);
    // if (mini->Camera)
    //     free(mini->Camera);
    // if (mini->Light)
    //     free(mini->Light);
    // free_Sphere(mini->Sphere);
    // free_Plane(mini->Plane);
    // free_Cylinder(mini->Cylinder);
    free_data(mini->Data);
    free(mini);
}
