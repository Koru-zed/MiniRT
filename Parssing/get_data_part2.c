 #include "../Include/miniRT.h"

int    get_Plane(t_minirt *mini, t_data *data)
{
    // int     empty;
    static  int i;
    // t_Plane *_plane;

    // empty = 1;
    // if (!mini->Plane)
    //     empty = 0;

    // _plane = ft_calloc(1, sizeof(t_Plane));

    set_cordinates(data->pars[1], &mini->Plane[i].ray.origin, mini);
    set_orientation(data->pars[2], &mini->Plane[i].ray.direction, mini);
    set_color(data->pars[3], mini->Plane[i].color, mini);
    i++;
    // if (empty)
    //     rt_last_Plane(mini->Plane)->next = _plane;
    // else
        // mini->Plane = _plane;
    return 1;
}

int    get_Sphere(t_minirt *mini, t_data *data)//**Spher
{
    // int      empty;
    static  int i;

    // t_Sphere *_sphere;

    // empty = 1;
    // if (!mini->Sphere)
    //     empty = 0;
    // _sphere = ft_calloc(1, sizeof(t_Sphere));
    set_cordinates(data->pars[1], &mini->Sphere[i].center, mini);
    mini->Sphere[i].radius = ft_atod(data->pars[2], &mini->check) / 2;
    if (mini->check)
    {
        free_mini(mini);
        exit(EXIT_FAILURE);
    }
    set_color(data->pars[3], mini->Sphere[i].color, mini);
    i++;
    // if (empty)
    //     rt_last_Sphere(mini->Sphere)->next = _sphere;
    // else
        // mini->Sphere = _sphere;
    return 1;
}

int    get_Cylinder(t_minirt *mini, t_data *data)
{
    // int         empty;
    static  int i;

    // t_Cylinder *_cylinder;

    // empty = 1;
    // if (!mini->Cylinder)
    //     empty = 0;
    // _cylinder = ft_calloc(1, sizeof(t_Cylinder));
    set_cordinates(data->pars[1], &mini->Cylinder[i].cordinates, mini);
    set_orientation(data->pars[2], &mini->Cylinder[i].orientation, mini);
	/*
	 *  todo : ! turn atod from double to float !
	 */
    mini->Cylinder[i].redius = ft_atod(data->pars[3], &mini->check) / 2;
    mini->Cylinder[i].height = ft_atod(data->pars[4], &mini->check);
    if (mini->check)
    {
        free_mini(mini);
        exit(EXIT_FAILURE);
    }
    set_color(data->pars[5], mini->Cylinder[i].color, mini);
    i++;
    // if (empty)
    //     rt_last_Cylinder(mini->Cylinder)->next = _cylinder;
    // else
        // mini->Cylinder = _cylinder;
    return 1;
}