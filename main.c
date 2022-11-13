#include "Include/miniRT.h"


long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

t_point	ray_pixel_to_world(t_minirt *mini, int x, int y)
{
	float	aspect_ratio;
	float	half_hight;
	float   half_width;
	float	p_x;
	float	p_y;

	half_hight = tanf((mini->Camera->fov * M_PI / 180) / 2);
	aspect_ratio = mini->Mlx->width / mini->Mlx->height;
	half_width = half_hight * aspect_ratio;
	p_x = (2 * (x + 0.5) / mini->Mlx->width - 1) * half_width;
	p_y = (1 - 2 * (y + 0.5) / mini->Mlx->height) * half_hight;
	return (new_point(-p_x, p_y, 1));
}

t_ray	ray_generator(t_minirt *mini, int x, int y)
{
	t_point	shooting_direction;
	t_ray	ray;

	shooting_direction = ray_pixel_to_world(mini->Camera, x, y);
	shooting_direction = mul_point_matrix(shooting_direction, mini->Camera->matrix);
	shooting_direction = v_sub(shooting_direction, mini->Camera->ray.origin);
	shooting_direction = normalizing(shooting_direction);
	ray.origin = mini->Camera->ray.origin;
	ray.direction = shooting_direction;
	return (ray);
}

// +


int main(int ac, char **av)
{
	// size_t t;
	int x, y;
    t_minirt *miniRT;
	t_ray	ray;
	int		color;
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
		fill_matrix(miniRT->Camera);
		miniRT->Mlx->width = WIDTH;
		miniRT->Mlx->height = HEIGHT;
		while (y < Mlx->height)
		{
			x = 0;
			while (x < Mlx->width)
			{
				ray = ray_generator(miniRT, x, y);
				// my_mlx_pixel_put(miniRT->Mlx, x, y, color);
				x++;
			}
			y++;
		}
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
