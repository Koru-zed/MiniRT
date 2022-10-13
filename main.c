#include "miniRT.h"

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
    printf("## Data ##\n");
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