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
        data->array = filename;
        data->pars = ft_split(data->array, ' ');
        return (1);
    }
    return (0);
}

void fill_data(t_data *p_data, t_data *n_data, int fd)
{
    n_data->check_empty = ft_check_valid(get_next_line(fd), n_data);
    if (n_data->check_empty == -1)
        return ;
    if (n_data->array)
    {
        n_data->prev = p_data;
        n_data->next = ft_calloc(1, sizeof(t_data));
        fill_data(n_data, n_data->next, fd);
        return ;
    }
    else
        fill_data(p_data, n_data, fd);
}

void    free_mini(t_mini *mini)
{
    t_data *next_data;

    next_data = NULL;
    if (mini->Ambient)
        mini->Ambient;
    if (mini->Camera)
        mini->Camera;
    if (mini->Light)
        mini->Light;
    if (mini->Sphere)
        mini->Sphere;
    if (mini->Plane)
        mini->Plane;
    if (mini->Cylinder)
        mini->Cylinder;
    while (data)
    {
        next_data = data->next;
        if (data->array)
            free(data->array);
        free(data);
    }
    free(mini);
}

void    set_cordinates(char const *cord, float *table)
{
    int     i;
    int     size;
    char    **arr;
    
    i = 0;
    arr = ft_split(cord, ',');
    size =sizeof(arr) / sizeof(char *);
    if (size != 3)
    {
        ft_putstr_fd("Error : Unknown information", 1);
        free_mini(mini);
        exit(EXIT_FAILURE);
    }
    table[0] = ft_atod(arr[0]);
    table[1] = ft_atod(arr[1]);
    table[2] = ft_atod(arr[2]);
    if (mini->check == -1)
    {
        free_mini(mini);
        exit(EXIT_FAILURE);
    }
}

void    set_orientation(char const *colors, float *table)
{
    int     i;
    int     size;
    char    **arr;
    
    i = -1;
    arr = ft_split(colors, ',');
    size =sizeof(arr) / sizeof(char *);
    if (size != 3)
    {
        ft_putstr_fd("Error : Unknown information", 1);
        free_mini(mini);
        exit(EXIT_FAILURE);
    }
    table[0] = ft_atod(arr[0]);
    table[1] = ft_atod(arr[1]);
    table[2] = ft_atod(arr[2]);
    while (table[++i])
    {
        if (mini->check == -1)
        {
            free_mini(mini);
            exit(EXIT_FAILURE);
        }
        if (table[i] < -1 && table[i] > 1))
        {
            ft_putstr_fd("Error : out of range [-1.0;1.0]", 1);
            mini->check = -1;
        }
    }
}

void    set_color(char const *colors, size_t *table)
{
    int     size;
    char    **arr;
    
    i = 0;
    j = i;
    arr = ft_split(colors, ',');
    size =sizeof(arr) / sizeof(char *);
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

void    get_Ambient_lightning(t_minirt *mini, t_data *data)
{
    if (!mini->Ambient->repetition)
    {
        mini->Ambient->repetition = 1;
        mini->Ambient->ratio = ft_atod(&(data->pars[0]), mini->check);
        if (mini->check == -1  || !(mini->Ambient->ratio >= 0 && mini->Ambient->ratio <= 1))
        {
            if (mini->check != -1)
                ft_putstr_fd("Error : out of range [0.0;1.0]", 1);// second statement
            free_mini(mini);
            exit(EXIT_FAILURE);
        }
        set_color(data->pars[1], mini->Ambient->color)
        return ;
    }
    ft_putstr_fd("Munltiple Ambient", 1);
    free_mini(mini);
    exit(EXIT_FAILURE);
}

void    get_Camera(t_minirt mini, t_data *data)
{   
    if (!mini->Camera->repetition)
    {
        mini->Camera->repetition = 1;
        set_cordinates(data->pars[0], mini->Camera->cordinates);
        // check_cordinates(mini->Cylinder->cordinates, 0.0, 0.0, 20.6);
        set_orientation(data->pars[1], mini->Camera->orientation);
        mini->Camera->fov = ft_atoi(data->pars[2]);
        if (mini->check || mini->Camera->fov < 0 && mini->Camera->fov > 180)
        {
            ft_putstr_fd("Error : out of range [0;180]", 1);
            free_mini(mini);
            exit(EXIT_FAILURE);
        }
        return ;
    }
    ft_putstr_fd("Munltiple Camera", 1);
    free_mini(mini);
    exit(EXIT_FAILURE);
}

void    get_Light(t_minirt mini, t_data *data)
{   
    if (!mini->Light->repetition)
    {
        mini->Light->repetition = 1;
        set_cordinates(data->pars[0], mini->Light->cordinates);
        // check_cordinates(mini->Cylinder->cordinates, 0.0, 0.0, 20.6);
        mini->Light->brightness = ft_atod(data->pars[1]);
        if (mini->check || mini->Light->brightness < 0 && mini->Light->bright > 1)
        {
            if (mini->check != -1)
                ft_putstr_fd("Error : out of range [0.0;1.0]", 1);
            free_mini(mini);
            exit(EXIT_FAILURE);
        }
        set_color(data->pars[2], mini->Light->color);
        retu
    ft_putstr_fd("Munltiple Light", 1);
    free_mini(mini);
    exit(EXIT_FAILURE);

}

void    get_Sphere(t_minirt mini, t_data *data)//**Spher
{
    set_cordinates(data->pars[0], mini->Sphere->cordinates);
    // check_cordinates(mini->Cylinder->cordinates, 0.0, 0.0, 20.6);
    mini->Sphere->diameter = ft_atod(data->pars[1]);
    if (mini->check || mini->Sphere->diameter != 12.6)
    {
        if (mini->check != -1)
            ft_putstr_fd("Error : bad value should be 12.6", 1);
        free_mini(mini);
        exit(EXIT_FAILURE);
    }
    set_color(data->pars[2], mini->Sphere->color);
}

void    get_Plane(t_minirt mini, t_data *data)
{
    set_cordinates(data->pars[0], mini->Plane->cordinates);
    // check_cordinates(mini->Cylinder->cordinates, 0.0, 0.0, -10.0);
    set_orientation(data->pars[1], mini->Plane->orientation);
    set_color(data->pars[2], mini->Plane->color);
}

void    get_Cylinder(t_minirt mini, t_data *data)
{
    set_cordinates(data->pars[0], mini->Cylinder->cordinates);
    // check_cordinates(mini->Cylinder->cordinates, 50.0, 0.0, 20.6);
    set_orientation(data->pars[1], mini->Cylinder->orientation);
    mini->Cylinder->diameter = ft_atod(data->pars[2]);
    mini->Cylinder->radius = ft_atod(data->pars[3]);
    if (mini->check || mini->Cylinder->diameter != 14.2 || mini->Cylinder->radius != 21.42)
    {
        if (mini->Cylinder->diameter != 14.2)
            ft_putstr_fd("Error : bad value should be 14.2", 1);
        else if (mini->Cylinder->radius != 21.42)
            ft_putstr_fd("Error : bad value should be 21.42", 1);
        free_mini(mini);
        exit(EXIT_FAILURE);
    }
    set_color(data->pars[4], mini->Cylinder->color);
}

size_t    check_data(t_minirt *mini, t_data *data)
{
    int     i;
    int     j;
    char    *str;

    j = 0;
    i = -1;
    // while (data->array[++i] == ' ');
    // while (ft_isalpha(data->array[i + j]))
    //     j++;
    // if (j > 2 && j < 1)
    //     return 0;
    // str = ft_substr(data->array, i, i + j);
    // data->array = str;
    // if (check_duplicut(mini)) //check  duplicut of data
    //     return 0;
    // while (data->pars[++i])
    // {
        if (!ft_strcmp(data->pars[0], ambient))
            get_Ambient_lightning(mini, data);
        if (!ft_strcmp(data->pars[0], camera))
            get_Camera(mini, data);
        if (!ft_strcmp(data->pars[0], light))
            get_Light(mini, data);
        if (!ft_strcmp(data->pars[0], plane))
            get_Plane(mini, data);
        if (!ft_strcmp(data->pars[0], sphre))
            get_Sphere(mini, data);
        if (!ft_strcmp(data->pars[0], cylinder))
            get_Cylinder(mini, data);
    // }
    if (!check)////////////////////////
        return 0;
    return 1;
}

void    ft_fill_Info(t_minirt *mini)
{
    t_data *_data;

    _data = mini->data;
    while (_data)
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
    miniRT->data = ft_calloc(1, sizeof(t_data));

    if (av[1])
    {
        miniRT->file = av[1];
        miniRT->fd = open(miniRT->file, O_RDONLY);
        fill_data(NULL, miniRT->data, miniRT->fd);   
    }
    Data = miniRT->data;
    while (Data && Data->check_empty == 1)
    {
        i = -1;
        while (Data->pars[++i])
            printf("|%s|  ", Data->pars[i]);
        printf ("\n");
        Data = Data->next;
    }
}