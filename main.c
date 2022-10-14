#include "miniRT.h"

void ray_render(t_minirt *pMinirt);

int main(int ac, char **av)
{
//    int i;
	void		*mlx;
	void		*mlx_window;
    t_minirt	*miniRT;
	t_mlx		data_mlx;
//    t_data *Data;

    miniRT = ft_calloc(1, sizeof(t_minirt));
    miniRT->Data = ft_calloc(1, sizeof(t_data));
    if (ac == 2)
    {
        miniRT->file = av[1];
        miniRT->fd = open(miniRT->file, O_RDONLY);
        fill_data(NULL, miniRT->Data, miniRT->fd);
        miniRT->Ambient = ft_calloc(1, sizeof(t_Ambient));
        miniRT->Camera = ft_calloc(1, sizeof(t_Camera));
        miniRT->Light = ft_calloc(1, sizeof(t_Light));
        fill_Info(miniRT);
		mlx = mlx_init();
		mlx_window = mlx_new_window(mlx, W_X, W_Y, "miniRT");
		data_mlx.img = mlx_new_image(mlx, W_X, W_Y);
		mlx_get_data_addr(mlx, &data_mlx.bits_per_pixel,
			  &data_mlx.line_length, &data_mlx.endian);
		ray_render(miniRT);
		mlx_put_image_to_window(mlx, mlx_window, data_mlx.img, 0, 0);
		mlx_loop(mlx);
    }
//   miniRT Data = miniRT->Data;
//    printf("## Data ##\n");
//    while (Data && Data->check_empty == 1)
//    {
//        i = -1;
//        while (Data->pars[++i])
//            printf("|%s|  ", Data->pars[i]);
//        printf ("\n");
//        Data = Data->next;
//    }
    free_mini(miniRT);
}
//void	add_tow_vectors();
void ray_render(t_minirt *pMinirt)
{

}






















