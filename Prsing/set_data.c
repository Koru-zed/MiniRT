#include "miniRT.h"

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
