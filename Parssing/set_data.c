#include "../Include/miniRT.h"

void    set_cordinates(char const *cord, t_point *cordinate, t_minirt *mini)
{
    int     size;
    char    **arr;
    
    arr = ft_split(cord, ',');
    size = ft_arrylen(arr);
    if (size != 3)
    {
        ft_putstr_fd("Error : Unknown information", 1);

        free_mini(mini);
        exit(EXIT_FAILURE);
    }
    cordinate->x = ft_atod(arr[0], &mini->check);
    cordinate->y = ft_atod(arr[1], &mini->check);
    cordinate->z = ft_atod(arr[2], &mini->check);
    if (mini->check == -1)
    {
        free_mini(mini);
        exit(EXIT_FAILURE);
    }
}

void    set_orientation(char const *colors, t_point *cordinate, t_minirt *mini)
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
    cordinate->x = ft_atod(arr[0], &mini->check);
    cordinate->y = ft_atod(arr[1], &mini->check);
    cordinate->z = ft_atod(arr[2], &mini->check);
    if (mini->check == -1 || (cordinate->x < -1 && cordinate->x > 1) || \
        (cordinate->y < -1 && cordinate->y > 1) || (cordinate->z < -1 && cordinate->z > 1))
    {
        ft_putstr_fd("Error : out of range [-1.0;1.0]", 1);
        free_mini(mini);
        exit(EXIT_FAILURE);
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
