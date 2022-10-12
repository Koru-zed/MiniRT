#include "miniRT.h"

int ft_check_valid(char *filename, t_data *data)
{
    int i;

    i = 0;
    if (!filename)
        return (-1);
    while (filename[i] && filename[i] == ' ')
        i++;
    if (filename[i] && filename[i] != '\n')
    {
        data->info = filename;
        data->pars = ft_split(data->info, ' ');
        return (1);
    }
    return (0);
}

void fill_data(t_data *p_data, t_data *n_data, int fd)
{
    n_data->check_empty = ft_check_valid(get_next_line(fd), n_data);
    if (n_data->check_empty == -1)
        return ;
    if (n_data->info)
    {
        n_data->prev = p_data;
        n_data->next = ft_calloc(1, sizeof(t_data));
        fill_data(n_data, n_data->next, fd);
        return ;
    }
    else
        fill_data(p_data, n_data, fd);
}




// t_Ambient *ft_alloc_Ambient()
// {
//     t_Ambient *_ambient;

//     _ambient = ft_calloc(1, sizeof(t_Ambient));
//     // _ambient->color = ft_calloc(3, sizeof(size_t));
//     // ft_bzero(_ambient->color, 3);
//     return (_ambient);
// }

// t_Camera *ft_alloc_Camera()
// {
//     t_Camera *_camera;

//     _camera = ft_calloc(1, sizeof(t_Camera));
//     // _camera->cordinates = ft_calloc(3, sizeof(float));
//     // _camera->orientation = ft_calloc(3, sizeof(float));
//     // ft_bzero(_camera->cordinates, 3);
//     // ft_bzero(_camera->orientation, 3);
//     return (_camera);
// }

// t_Light *ft_alloc_Light()
// {
//     t_Light *_light;

//     _light = ft_calloc(1, sizeof(t_Light));
//     // _light->cordinates = ft_calloc(3, sizeof(float));
//     // _light->color = ft_calloc(3, sizeof(size_t));
//     // ft_bzero(_light->cordinates, 3);
//     // ft_bzero(_light->color, 3);
//     return (_light);
// }

// t_Plane *ft_alloc_Plane()
// {
//     t_Plane *_plane;

//     _plane = ft_calloc(1, sizeof(t_Plane));
//     // _plane->cordinates = ft_calloc(3, sizeof(float));
//     // _plane->orientation = ft_calloc(3, sizeof(float));
//     // _plane->color = ft_calloc(3, sizeof(size_t));
//     // ft_bzero(_plane->cordinates, 3);
//     // ft_bzero(_plane->orientation, 3);
//     // ft_bzero(_plane->color, 3);
//     return (_plane);
// }

// t_Sphere *ft_alloc_Sphere()
// {
//     t_Sphere *_sphere;

//     _sphere = ft_calloc(1, sizeof(t_Sphere));
//     // ft_bzero(_sphere->cordinates, 3);
//     // ft_bzero(_sphere->color, 3);
//     // _sphere->cordinates = ft_calloc(3, sizeof(float));
//     // _sphere->color = ft_calloc(3, sizeof(size_t));
//     return (_sphere);
// }

// t_Cylinder *ft_alloc_Cylinder()
// {
//     t_Cylinder *_cylinder;

//     _cylinder = ft_calloc(1, sizeof(t_Cylinder));
//     // ft_bzero(_cylinder->cordinates, 3);
//     // ft_bzero(_cylinder->orientation, 3);
//     // ft_bzero(_cylinder->color, 3);
//     // _cylinder->cordinates = ft_calloc(3, sizeof(float));
//     // _cylinder->orientation = ft_calloc(3, sizeof(float));
//     // _cylinder->color = ft_calloc(3, sizeof(size_t));
//     return (_cylinder);
// }





// t_Plane *get_node_Plane(t_Plane *_plane)
// {
//     size_t     i;
//     t_Plane    *node;

//     node = _plane;
//     i = node->repetition;
//     while (i--)
// {        node = node->next;
//         node = ft_calloc(1, sizeof(t_Plane));
// }
//     // t_Plane    *head;

//     // node = *_plane;
//     // head = node;
//     // while (--i)
//     // {
//     //     node = node->next;
//     // }
//     // *_plane = head;
//     return (node);
// }



size_t    check_data(t_minirt *mini, t_data *data)
{

    // while (data->info[++i] == ' ');
    // while (ft_isalpha(data->info[i + j]))
    //     j++;
    // if (j > 2 && j < 1)
    //     return 0;
    // str = ft_substr(data->info, i, i + j);
    // data->info = str;
    // if (check_duplicut(mini)) //check  duplicut of data
    //     return 0;
    // while (data->pars[++i])
    // {
        if (!ft_strcmp(data->pars[0], ambient) && get_Ambient_lightning(mini, data))
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
////////////////////////////////////////////////////////////////////////////////////////////////
        else if (!ft_strcmp(data->pars[0], camera) && get_Camera(mini, data)) 
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
////////////////////////////////////////////////////////////////////////////////////////////////
        else if (!ft_strcmp(data->pars[0], light) && get_Light(mini, data))            
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
////////////////////////////////////////////////////////////////////////////////////////////////
        else if (!ft_strcmp(data->pars[0], sphre) && get_Sphere(mini, data)) 
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
////////////////////////////////////////////////////////////////////////////////////////////////
        else if (!ft_strcmp(data->pars[0], plane) && get_Plane(mini, data)) 
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
////////////////////////////////////////////////////////////////////////////////////////////////
        else if (!ft_strcmp(data->pars[0], cylinder) && get_Cylinder(mini, data)) 
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
    // if (!mini->check)////////////////////////
    //     return 0;
    return 1;
}

void    fill_Info(t_minirt *mini)
{
    t_data *_data;

    _data = mini->Data;
    while (_data && _data->info)
    {
        if (!check_data(mini, _data))
            return ;
        _data = _data->next;
    }
}


int main(int ac, char **av)
{
    int i;
    t_minirt *miniRT;
    t_data *Data;

    (void)ac;
    miniRT = ft_calloc(1, sizeof(t_minirt));
    miniRT->Data = ft_calloc(1, sizeof(t_data));

    if (av[1])
    {
        miniRT->file = av[1];
        miniRT->fd = open(miniRT->file, O_RDONLY);
        fill_data(NULL, miniRT->Data, miniRT->fd);
        miniRT->Ambient = ft_calloc(1, sizeof(t_Ambient));
        miniRT->Camera = ft_calloc(1, sizeof(t_Camera));
        miniRT->Light = ft_calloc(1, sizeof(t_Light));
        fill_Info(miniRT);
    }
    Data = miniRT->Data;
    while (Data && Data->check_empty == 1)
    {
        i = -1;
        while (Data->pars[++i])
            printf("|%s|  ", Data->pars[i]);
        printf ("\n");
        Data = Data->next;
    }
    free_mini(miniRT);
}