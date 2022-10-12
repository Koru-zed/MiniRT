#include "../miniRT.h"

int    get_Ambient_lightning(t_minirt *mini, t_data *data)
{
    if (!mini->Ambient->repetition)
    {
        mini->Ambient->repetition = 1;
        if (ft_arrylen(data->pars) != 2)
            ret
        mini->Ambient->ratio = ft_atod(data->pars[1], &mini->check);
        if (mini->check == -1  || !(mini->Ambient->ratio >= 0.0f && mini->Ambient->ratio <= 1.0f))
        {
            if (mini->check != -1)
                ft_putstr_fd("Error : out of range [0.0;1.0]", 1);// second statement
            free_mini(mini);
            exit(EXIT_FAILURE);
        }
        set_color(data->pars[2], mini->Ambient->color, mini);
        return 1;
    }
    ft_putstr_fd("Munltiple Ambient", 1);
    free_mini(mini);
    exit(EXIT_FAILURE);
    return 0;
}

int    get_Camera(t_minirt *mini, t_data *data)
{   
    if (!mini->Camera->repetition)
    {
        mini->Camera->repetition = 1;
        set_cordinates(data->pars[1], mini->Camera->cordinates, mini);
        // check_cordinates(mini->Cylinder->cordinates, 0.0, 0.0, 20.6);
        set_orientation(data->pars[2], mini->Camera->orientation, mini);
        mini->Camera->fov = ft_atoi(data->pars[3]);
        if (mini->check || (mini->Camera->fov < 0 && mini->Camera->fov > 180))
        {
            ft_putstr_fd("Error : out of range [0;180]", 1);
            free_mini(mini);
            exit(EXIT_FAILURE);
        }
        return 1;
    }
    ft_putstr_fd("Munltiple Camera", 1);
    free_mini(mini);
    exit(EXIT_FAILURE);
    return 0;
}

int    get_Light(t_minirt *mini, t_data *data)
{   
    if (!mini->Light->repetition)
    {
        mini->Light->repetition = 1;
        set_cordinates(data->pars[1], mini->Light->cordinates, mini);
        // check_cordinates(mini->Cylinder->cordinates, 0.0, 0.0, 20.6);
        mini->Light->brightenss = ft_atod(data->pars[2], &mini->check);
        if (mini->check || (mini->Light->brightenss < 0.0f && mini->Light->brightenss > 1.0f))
        {
            if (mini->check != -1)
                ft_putstr_fd("Error : out of range [0.0;1.0]", 1);
            free_mini(mini);
            exit(EXIT_FAILURE);
        }
        set_color(data->pars[3], mini->Light->color, mini);
        return 1;
    }
    ft_putstr_fd("Munltiple Light", 1);
    free_mini(mini);
    exit(EXIT_FAILURE);
    return 0;
}