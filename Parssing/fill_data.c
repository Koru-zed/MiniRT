#include "../miniRT.h"

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
