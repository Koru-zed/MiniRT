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
    if (mini->Sphere)
        free(mini->Sphere);
    if (mini->Plane)
        free(mini->Plane);
    if (mini->Cylinder)
        free(mini->Cylinder);
    while (mini->data)
    {
        next_data = mini->data->next;
        if (mini->data->array)
            free(mini->data->array);
        if (mini->data->pars)
        {
            while (mini->data->pars[++i])
                free(mini->data->pars[i]);
            free(mini->data->pars);
        }
        free(mini->data);
        mini->data = next_data;
    }
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

int    get_Plane(t_minirt *mini, t_data *data)
{
    set_cordinates(data->pars[1], mini->Plane->cordinates, mini);
    // check_cordinates(mini->Cylinder->cordinates, 0.0, 0.0, -10.0);
    set_orientation(data->pars[2], mini->Plane->orientation, mini);
    set_color(data->pars[3], mini->Plane->color, mini);
    return 1;
}

int    get_Sphere(t_minirt *mini, t_data *data)//**Spher
{
    set_cordinates(data->pars[1], mini->Sphere->cordinates, mini);
    // check_cordinates(mini->Cylinder->cordinates, 0.0, 0.0, 20.6);
    mini->Sphere->diameter = ft_atod(data->pars[2], &mini->check);
    if (mini->check || mini->Sphere->diameter != 12.6f)
    {
        if (mini->check != -1)
            ft_putstr_fd("Error : bad value should be 12.6", 1);
        free_mini(mini);
        exit(EXIT_FAILURE);

    }
    set_color(data->pars[3], mini->Sphere->color, mini);
    return 1;
}

int    get_Cylinder(t_minirt *mini, t_data *data)
{
    set_cordinates(data->pars[1], mini->Cylinder->cordinates, mini);
    // check_cordinates(mini->Cylinder->cordinates, 50.0, 0.0, 20.6);
    set_orientation(data->pars[2], mini->Cylinder->orientation, mini);
    mini->Cylinder->diameter = ft_atod(data->pars[3], &mini->check);
    mini->Cylinder->hright = ft_atod(data->pars[4], &mini->check);
    if (mini->check || mini->Cylinder->diameter != 14.2f || mini->Cylinder->hright != 21.42f)
    {
        if (mini->Cylinder->diameter != 14.2f)
            ft_putstr_fd("Error : bad value should be 14.2", 1);
        else if (mini->Cylinder->hright != 21.42f)
            ft_putstr_fd("Error : bad value should be 21.42", 1);
        free_mini(mini);
        exit(EXIT_FAILURE);
    }
    set_color(data->pars[5], mini->Cylinder->color, mini);
    return 1;
}

size_t    check_data(t_minirt *mini, t_data *data)
{

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
        if (!ft_strcmp(data->pars[0], ambient) && get_Ambient_lightning(mini, data))
            {
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
                printf("************************\n");
                printf("diameter [%f]\n", mini->Sphere->diameter);
                printf("X [%f]\n", mini->Sphere->cordinates[0]);
                printf("Y [%f]\n", mini->Sphere->cordinates[1]);
                printf("Z [%f]\n", mini->Sphere->cordinates[2]);
                    printf("   -----  \n");
                printf("R [%zu]\n", mini->Sphere->color[0]);
                printf("G [%zu]\n", mini->Sphere->color[1]);
                printf("B [%zu]\n", mini->Sphere->color[2]);
                printf("************************\n");
            }
////////////////////////////////////////////////////////////////////////////////////////////////
        else if (!ft_strcmp(data->pars[0], plane) && get_Plane(mini, data)) 
            {
                printf("************************\n");
                printf("X [%f]\n", mini->Plane->cordinates[0]);
                printf("Y [%f]\n", mini->Plane->cordinates[1]);
                printf("Z [%f]\n", mini->Plane->cordinates[2]);
                    printf("   -----  \n");
                printf("X.o_v [%f]\n", mini->Plane->orientation[0]);
                printf("Y.o_v [%f]\n", mini->Plane->orientation[1]);
                printf("Z.o_v [%f]\n", mini->Plane->orientation[2]);
                    printf("   -----  \n");
                printf("R [%zu]\n", mini->Plane->color[0]);
                printf("G [%zu]\n", mini->Plane->color[1]);
                printf("B [%zu]\n", mini->Plane->color[2]);
                printf("************************\n");
            }
////////////////////////////////////////////////////////////////////////////////////////////////
        else if (!ft_strcmp(data->pars[0], cylinder) && get_Cylinder(mini, data)) 
           {
                printf("************************\n");
                printf("diameter [%f]\n", mini->Cylinder->diameter);
                printf("hright [%f]\n", mini->Cylinder->hright);
                printf("X [%f]\n", mini->Cylinder->cordinates[0]);
                printf("Y [%f]\n", mini->Cylinder->cordinates[1]);
                printf("Z [%f]\n", mini->Cylinder->cordinates[2]);
                    printf("   -----  \n");
                printf("X.o_v [%f]\n", mini->Cylinder->orientation[0]);
                printf("Y.o_v [%f]\n", mini->Cylinder->orientation[1]);
                printf("Z.o_v [%f]\n", mini->Cylinder->orientation[2]);
                    printf("   -----  \n");
                printf("R [%zu]\n", mini->Cylinder->color[0]);
                printf("G [%zu]\n", mini->Cylinder->color[1]);
                printf("B [%zu]\n", mini->Cylinder->color[2]);
                printf("************************\n");
            }
    // if (!mini->check)////////////////////////
    //     return 0;
    return 1;
}

void    fill_Info(t_minirt *mini)
{
    t_data *_data;

    _data = mini->data;
    while (_data && _data->array)
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
        miniRT->Ambient = ft_calloc(1, sizeof(t_Ambient));
        miniRT->Camera = ft_calloc(1, sizeof(t_Camera));
        miniRT->Light = ft_calloc(1, sizeof(t_Light));
        miniRT->Sphere = ft_calloc(1, sizeof(t_Sphere));
        miniRT->Plane = ft_calloc(1, sizeof(t_Plane));
        miniRT->Cylinder = ft_calloc(1, sizeof(t_Cylinder));
        fill_Info(miniRT);
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