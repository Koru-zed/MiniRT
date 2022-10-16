#include "../Include/miniRT.h"

size_t    check_data(t_minirt *mini, t_data *data)
{
        if (!ft_strcmp(data->pars[0], ambient))
        {
            get_Ambient_lightning(mini, data);
            {
                printf("-- Ambient --\n");
                printf("************************\n");
                printf("repetition [%zu]\n", mini->Ambient->repetition);
                printf("ratio [%f]\n", mini->Ambient->ratio);
                printf("R [%zu]\n", mini->Ambient->color[0]);
                printf("G [%zu]\n", mini->Ambient->color[1]);
                printf("B [%zu]\n", mini->Ambient->color[2]);
                printf("************************\n");
            }
        }
////////////////////////////////////////////////////////////////////////////////////////////////
        else if (!ft_strcmp(data->pars[0], camera)){
            get_Camera(mini, data);
            {
                printf("-- Camera --\n");
                printf("************************\n");
                printf("repetition [%zu]\n", mini->Camera->repetition);
                printf("FOV [%zu]\n", mini->Camera->fov);
                printf("X [%f]\n", mini->Camera->cordinates[0]);
                printf("Y [%f]\n", mini->Camera->cordinates[1]);
                printf("Z [%f]\n", mini->Camera->cordinates[2]);
                    printf("   -----  \n");
                printf("X.o_v [%f]\n", mini->Camera->orientation[0]);
                printf("Y.o_v [%f]\n", mini->Camera->orientation[1]);
                printf("Z.o_v [%f]\n", mini->Camera->orientation[2]);
                printf("************************\n");
            }
        }
////////////////////////////////////////////////////////////////////////////////////////////////
        else if (!ft_strcmp(data->pars[0], light)){
            get_Light(mini, data);          
            {
                printf("-- Light --\n");
                printf("************************\n");
                printf("repetition [%zu]\n", mini->Light->repetition);
                printf("brightenss [%f]\n", mini->Light->brightenss);
                printf("X [%f]\n", mini->Light->cordinates[0]);
                printf("Y [%f]\n", mini->Light->cordinates[1]);
                printf("Z [%f]\n", mini->Light->cordinates[2]);
                    printf("   -----  \n");
                printf("R [%zu]\n", mini->Light->color[0]);
                printf("G [%zu]\n", mini->Light->color[1]);
                printf("B [%zu]\n", mini->Light->color[2]);
                printf("************************\n");
            }
        }
////////////////////////////////////////////////////////////////////////////////////////////////
        else if (!ft_strcmp(data->pars[0], sphre)){
            get_Sphere(mini, data);
            {
                printf("-- Sphere --\n");
                printf("************************\n");
                printf("diameter [%f]\n", rt_last_Sphere(mini->Sphere)->diameter);
                printf("X [%f]\n", rt_last_Sphere(mini->Sphere)->cordinates[0]);
                printf("Y [%f]\n", rt_last_Sphere(mini->Sphere)->cordinates[1]);
                printf("Z [%f]\n", rt_last_Sphere(mini->Sphere)->cordinates[2]);
                    printf("   -----  \n");
                printf("R [%zu]\n", rt_last_Sphere(mini->Sphere)->color[0]);
                printf("G [%zu]\n", rt_last_Sphere(mini->Sphere)->color[1]);
                printf("B [%zu]\n", rt_last_Sphere(mini->Sphere)->color[2]);
                printf("************************\n");
            }
        }
////////////////////////////////////////////////////////////////////////////////////////////////
        else if (!ft_strcmp(data->pars[0], plane)){
            get_Plane(mini, data);
            {
                printf ("-- Plan --\n");
                printf("************************\n");
                printf("X [%f]\n", rt_last_Plane(mini->Plane)->cordinates[0]);
                printf("Y [%f]\n", rt_last_Plane(mini->Plane)->cordinates[1]);
                printf("Z [%f]\n", rt_last_Plane(mini->Plane)->cordinates[2]);
                    printf("   -----  \n");
                printf("X.o_v [%f]\n", rt_last_Plane(mini->Plane)->orientation[0]);
                printf("Y.o_v [%f]\n", rt_last_Plane(mini->Plane)->orientation[1]);
                printf("Z.o_v [%f]\n", rt_last_Plane(mini->Plane)->orientation[2]);
                    printf("   -----  \n");
                printf("R [%zu]\n", rt_last_Plane(mini->Plane)->color[0]);
                printf("G [%zu]\n", rt_last_Plane(mini->Plane)->color[1]);
                printf("B [%zu]\n", rt_last_Plane(mini->Plane)->color[2]);
                printf("************************\n");
            // exit (1);
            }
        }
////////////////////////////////////////////////////////////////////////////////////////////////
        else if (!ft_strcmp(data->pars[0], cylinder)){
            get_Cylinder(mini, data);
           {
                printf("-- Cylinder --\n");
                printf("************************\n");
                printf("diameter [%f]\n", rt_last_Cylinder(mini->Cylinder)->diameter);
                printf("hright [%f]\n", rt_last_Cylinder(mini->Cylinder)->hright);
                printf("X [%f]\n", rt_last_Cylinder(mini->Cylinder)->cordinates[0]);
                printf("Y [%f]\n", rt_last_Cylinder(mini->Cylinder)->cordinates[1]);
                printf("Z [%f]\n", rt_last_Cylinder(mini->Cylinder)->cordinates[2]);
                    printf("   -----  \n");
                printf("X.o_v [%f]\n", rt_last_Cylinder(mini->Cylinder)->orientation[0]);
                printf("Y.o_v [%f]\n", rt_last_Cylinder(mini->Cylinder)->orientation[1]);
                printf("Z.o_v [%f]\n", rt_last_Cylinder(mini->Cylinder)->orientation[2]);
                    printf("   -----  \n");
                printf("R [%zu]\n", rt_last_Cylinder(mini->Cylinder)->color[0]);
                printf("G [%zu]\n", rt_last_Cylinder(mini->Cylinder)->color[1]);
                printf("B [%zu]\n", rt_last_Cylinder(mini->Cylinder)->color[2]);
                printf("************************\n");
            }
        }
       else if (mini->check == -1)
            return (0);
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
