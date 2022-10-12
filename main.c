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

void free_Sphere(t_Sphere *_Sphere)
{
    t_Sphere *tmp;

    tmp = NULL;
    while (_Sphere)
    {
        tmp = _Sphere->next;
        free(_Sphere);
        _Sphere = tmp;
    }
}

void free_Plane(t_Plane *_Plane)
{
    t_Plane *tmp;

    tmp = NULL;
    while (_Plane)
    {
        tmp = _Plane->next;
        free(_Plane);
        _Plane = tmp;
    }
}

void free_Cylinder(t_Cylinder *_Cylinder)
{
    t_Cylinder *tmp;

    tmp = NULL;
    while (_Cylinder)
    {
        tmp =_Cylinder->next;
        free(_Cylinder);
        _Cylinder = tmp;
    }
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
    int     i;
    t_data  *next_data;

    i = -1;
    next_data = NULL;
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

void    set_cordinates(char const *cord, float *table, t_minirt *mini)
{
    int     i;
    int     size;
    char    **arr;
    
    i = 0;
    arr = ft_split(cord, ',');
    size = ft_arrylen(arr);
    if (size != 3)
    {
        ft_putstr_fd("Error : Unknown information", 1);
        free_mini(mini);
        exit(EXIT_FAILURE);
    }
    table[0] = ft_atod(arr[0], &mini->check);
    table[1] = ft_atod(arr[1], &mini->check);
    table[2] = ft_atod(arr[2], &mini->check);
    if (mini->check == -1)
    {
        free_mini(mini);
        exit(EXIT_FAILURE);
    }
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

void    set_orientation(char const *colors, float *table, t_minirt *mini)
{
    int     i;
    int     size;
    char    **arr;
    
    i = -1;
    arr = ft_split(colors, ',');
    size = ft_arrylen(arr);
    if (size != 3)
    {
        ft_putstr_fd("Error : Unknown information", 1);
        free_mini(mini);
        exit(EXIT_FAILURE);
    }
    table[0] = ft_atod(arr[0], &mini->check);
    table[1] = ft_atod(arr[1], &mini->check);
    table[2] = ft_atod(arr[2], &mini->check);
    while (table[++i])
    {
        if (mini->check == -1)
        {
            free_mini(mini);
            exit(EXIT_FAILURE);
        }
        if (table[i] < -1 && table[i] > 1)
        {
            ft_putstr_fd("Error : out of range [-1.0;1.0]", 1);
            mini->check = -1;
        }
    }
}

void    set_color(char const *colors, size_t *table, t_minirt *mini)
{
    int     size;
    char    **arr;

    arr = ft_split(colors, ',');
    size = ft_arrylen(arr);
    if (size != 3)
    {
        ft_putstr_fd("Error : Unknown information", 1);
        free_mini(mini);
        exit(EXIT_FAILURE);
    }
    table[0] = ft_atoi(arr[0]);
    table[1] = ft_atoi(arr[1]);
    table[2] = ft_atoi(arr[2]);
    if (table[0] > 255 || table[1] > 255 || table[2] > 255)
    {
        ft_putstr_fd("Error : out of range [0;255]", 1);
        free_mini(mini);
        exit(EXIT_FAILURE);
    }
}

int    get_Ambient_lightning(t_minirt *mini, t_data *data)
{
    if (!mini->Ambient->repetition)
    {
        mini->Ambient->repetition = 1;
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

t_Plane	*rt_last_Plane(t_Plane *Plane)
{
	t_Plane     *p_lst;
	p_lst = Plane;
	if (p_lst)
	{
		while (p_lst->next)
			p_lst = p_lst->next;
	}
	return (p_lst);
}

t_Sphere	*rt_last_Sphere(t_Sphere *Sphere)
{
	t_Sphere     *s_lst;

	s_lst = Sphere;
	if (s_lst)
	{
		while (s_lst->next)
			s_lst = s_lst->next;
	}
	return (s_lst);
}

t_Cylinder	*rt_last_Cylinder(t_Cylinder *Cylinder)
{
	t_Cylinder     *c_lst;

	c_lst = Cylinder;
	if (c_lst)
	{
		while (c_lst->next)
			c_lst = c_lst->next;
	}
	return (c_lst);
}
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

int    get_Plane(t_minirt *mini, t_data *data)
{
    int     empty;
    t_Plane *_plane;

    empty = 1;
    if (!mini->Plane)
        empty = 0;
    _plane = ft_calloc(1, sizeof(t_Plane));
    set_cordinates(data->pars[1], _plane->cordinates, mini);
    set_orientation(data->pars[2], _plane->orientation, mini);
    set_color(data->pars[3], _plane->color, mini);
    if (empty)
        rt_last_Plane(mini->Plane)->next = _plane;
    else
        mini->Plane = _plane;
    return 1;
}

int    get_Sphere(t_minirt *mini, t_data *data)//**Spher
{
    int      empty;
    t_Sphere *_sphere;

    empty = 1;
    if (!mini->Sphere)
        empty = 0;
    _sphere = ft_calloc(1, sizeof(t_Sphere));
    set_cordinates(data->pars[1], _sphere->cordinates, mini);
    _sphere->diameter = ft_atod(data->pars[2], &mini->check);
    if (mini->check)
    {
        free_mini(mini);
        exit(EXIT_FAILURE);
    }
    set_color(data->pars[3], _sphere->color, mini);
    if (empty)
        rt_last_Sphere(mini->Sphere)->next = _sphere;
    else
        mini->Sphere = _sphere;
    return 1;
}

int    get_Cylinder(t_minirt *mini, t_data *data)
{
    int         empty;
    t_Cylinder *_cylinder;

    empty = 1;
    if (!mini->Cylinder)
        empty = 0;
    _cylinder = ft_calloc(1, sizeof(t_Cylinder));
    set_cordinates(data->pars[1], _cylinder->cordinates, mini);
    set_orientation(data->pars[2], _cylinder->orientation, mini);
    _cylinder->diameter = ft_atod(data->pars[3], &mini->check);
    _cylinder->hright = ft_atod(data->pars[4], &mini->check);
    if (mini->check)
    {
        free_mini(mini);
        exit(EXIT_FAILURE);
    }
    set_color(data->pars[5], _cylinder->color, mini);
    if (empty)
        rt_last_Cylinder(mini->Cylinder)->next = _cylinder;
    else
        mini->Cylinder = _cylinder;
    return 1;
}

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