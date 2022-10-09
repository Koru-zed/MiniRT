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
        // data->check_empty = data->next->check_empty;
    }
    else
        fill_data(p_data, n_data, fd);
}

// void    set_color(char const *colors, t_mini *mini)
// {
//     int i;
//     int	j;

//     i = 0;
//     j = i;
//     skip_digit(colors, &i);
//     if (colors[i++] == ',')
//     {
//         j = i;
//         mini->Ambient->color[0] = ft_atoi(&colors[j]);
//         skip_digit(colors, &i);
//         if (colors[i++] == ',')
//         {
//             i = j;
//             mini->Ambient->color[1] = ft_atoi(&colors[j]);
//             skip_digit(colors, &i);
//             mini->Ambient->color[2] = ft_atoi(&colors[j]);
//             if (ft_isalpha(colors[i])
//                 mini->check = false;
//         }
//     }
//     if (!mini->check)
//     {
//         ft_putstr_fd("Error : color doesn't exist", 1);
//         exit(EXIT_FAILURE);
//     }
// }

// void    skip_space(char const *string, int *j)
// {
//     while (string[*j] == ' ')
//         *j++;
//     *j--;
// }

// void    skip_digit(char const *string, int *j)
// {
//     while (ft_isdigit(string[*j]))
//         *j++;
//     *j--;
// }

// void    get_Ambient_lightning(t_minirt *mini, t_data *data, int i)
// {
//     if (mini->Ambient->repetition)
//     {
//         mini->Ambient->repetition = true;
//         skip_space(data->array, &i);
//         if (!ft_isdigit(data->arry[i]))
//             break;
//         mini->Ambient->ratio = ft_atod(&(data->arry[i]), &i);
//         if (mini->Ambient->ratio && data->arry[i])
//         {
//             skip_space(data->array, &i);
//             set_color(&(data->array[i]), mini)
//         }
//     }
//     mini->check = false;
//     ft_putstr_fd("Munltiple Ambient", 1);
// }

// void    get_Camera(t_minirt mini, t_data *data, int i)
// {   
//     if (!mini->Camera->repetition)
//     {
//         mini->Camera->repetition = true;
//             while (data->array[i])
//             {
//                 skip_space(&i);
//                 if (!ft_isdigit(data->arry[i]))
//                     break;
//                 ;
//                 i++;
//             }
//             if (data->arry[i])
//                 mini->check = true;
//     }
//     mini->check = false;
//     ft_putstr_fd("Munltiple Camera", 1);
// }

// void    get_Light(t_minirt mini, t_data *data, int i)
// {   
//     if (!mini->Light->repetition)
//     {
//         mini->Light->repetition = true;
//             while (data->array[i])
//             {
//                 skip_space(&i);
//                 if (!ft_isdigit(data->arry[i]))
//                     break;
//                 ;
//                 i++;
//             }
//             if (data->arry[i])
//                 mini->check = true;
//     }
//     mini->check = false;
//     ft_putstr_fd("Munltiple Light", 1);

// }

// void    get_Sphere(t_minirt mini, t_data *data, int i)
// {
//         if (mini->Sphere[0] > 0)
//         {
//             while (data->array[i])
//             {
//                 skip_space(&i);
//                 if (!ft_isdigit(data->arry[i]))
//                     break;
//                 ;
//                 i++;
//             }
//             if (data->arry[i])
//                 mini->check = true;
//             mini->check = false;
//         }

// }

// void    get_Plane(t_minirt mini, t_data *data, int i)
// {
//         if (mini->Plane[0] > 1)
//         {
//             while (data->array[i])
//             {
//                 skip_space(&i);
//                 if (!ft_isdigit(data->arry[i]))
//                     break;
//                 ;
//                 i++;
//             }
//             if (data->arry[i])
//                 mini->check = true;
//             mini->check = false;
//         }

// }

// void    get_Cylinder(t_minirt mini, t_data *data, int i)
// {
//         if (mini->Cylinder[0] > 1)
//         {
//             while (data->array[i])
//             {
//                 ;
//                 i++;
//             }
//             mini->check = true;
//         }

// }

// size_t    check_data(t_minirt *mini, t_data *data)
// {
//     int     i;
//     int     j;
//     char    *str;

//     j = 0;
//     i = -1;
//     while (data->array[++i] == ' ');
//     while (ft_isalpha(data->array[i + j]))
//         j++;
//     if (j > 2 && j < 1)
//         return false;
//     str = ft_substr(data->array, i, i + j);
//     data->array = str;
//     // if (check_duplicut(mini)) //check  duplicut of data
//     //     return false;

//     // if (!ft_strcmp(str, Ambient))
//     //     get_Ambient_lightning(mini, data, i + j);
//     // if (!ft_strcmp(str, Camera))
//     //     get_Camera(mini, data, i + j);
//     // if (!ft_strcmp(str, Light))
//     //     get_Light(mini, data, i + j);
//     // if (!ft_strcmp(str, Plane))
//     //     get_Plane(mini, data, i + j);
//     // if (!ft_strcmp(str, Sphre))
//     //     get_Sphere(mini, data, i + j);
//     // if (!ft_strcmp(str, Cylinder))
//     //     get_Cylinder(mini, data, i + j);
//     // if (!check)
//     //     return false;
//     return true;
// }

// void    ft_fill_Info(t_minirt *mini)
// {
//     t_data *_data;

//     _data = mini->data;
//     while (_data)
//     {
//         if (!check_data(mini, _data))
//             return ;
//         _data = _data->next;
//     }
// }

int main(int ac, char **av)
{
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
    while (Data)
    {
        printf("%s", Data->array);
        Data = Data->next;
}
    }