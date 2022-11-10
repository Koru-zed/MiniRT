#include "Include/miniRT.h"


long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int main(int ac, char **av)
{
	// size_t t;
	// int y;
    t_minirt *miniRT;

    // t_data *Data;

	(void)ac;
	(void)av;
	miniRT = ft_calloc(1, sizeof(t_minirt));
	miniRT->Data = ft_calloc(1, sizeof(t_data));
	if (av[1])
	{
		miniRT->file = av[1];
		miniRT->fd = open(miniRT->file, O_RDONLY);
		fill_data(miniRT->Data, miniRT->fd);
		miniRT->Ambient = ft_calloc(1, sizeof(t_Ambient));
		miniRT->Camera = ft_calloc(1, sizeof(t_Camera));
		miniRT->Light = ft_calloc(1, sizeof(t_Light));
		fill_Info(miniRT);

		// miniRT->Mlx = ft_calloc(1, sizeof(t_mlx));
		// miniRT->Mlx->mlx = mlx_init();
		// miniRT->Mlx->win = mlx_new_window(miniRT->Mlx->mlx, 720, 540, "miniRT");
		// miniRT->Mlx->img = mlx_new_image(miniRT->Mlx->mlx, 720, 540);
		// miniRT->Mlx->addr = mlx_get_data_addr(
		// 		miniRT->Mlx->img, &miniRT->Mlx->bits_per_pixel, &miniRT->Mlx->line_length, &miniRT->Mlx->endian
		// 									 );
		// t = get_time();
		// ray_render(miniRT);
		// printf("-----------------------\n");
		// printf("Time measured: %lld ms.\n", get_time() - t);
		// mlx_put_image_to_window(miniRT->Mlx->mlx, miniRT->Mlx->win, miniRT->Mlx->img, 0, 0);
		// mlx_loop(miniRT->Mlx->mlx);
	}
    free_mini(miniRT);
}
