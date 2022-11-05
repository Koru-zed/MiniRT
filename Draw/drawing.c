#include "../Include/miniRT.h"

void	my_mlx_pixel_put(t_mlx *Mlx, int x, int y, int color)
{
	char	*dst;

	dst = Mlx->addr + (y * Mlx->line_length + x * (Mlx->bits_per_pixel >> 3));
	*(unsigned int*)dst = color;
	// printf("color[%d]\n", color);
}


static int	ft_parameters(t_mlx *info, int *x,int *y)
{
	info->d[0] = abs(x[1] - x[0]);
	info->d[1] = abs(y[1] - y[0]);
	if (x[0] < x[1])
		info->s[0] = 1;
	else
		info->s[0] = -1;
	if (y[0] < y[1])
		info->s[1] = 1;
	else
		info->s[1] = -1;
	return (info->d[0] - info->d[1]);
}

static void	set_coordinates_to_draw(t_mlx *info, int *x, int *y)
{
		x[0] = 50;
		y[0] = info->y[0];// = 50;
		x[1] = 700;
		y[1] = 175;
}

//// Brensham algo ////
void	draw_line(t_mlx *info, int color)
{
	int	p;
	int	d;
	int x[2];
	int y[2];
	set_coordinates_to_draw(info, x, y);
	d = ft_parameters(info, x, y);
	p = 2 * info->d[1] - info->d[0];
	while (x[0] != x[1] || y[0] != y[1])
	{
		my_mlx_pixel_put(info, x[0], y[0], color);
		if (x[0] == x[1] && y[0] == y[1])
			break ;
		x[0] += info->s[0];
		if (p < 0)
			p = p + 2 * info->d[1];
		else if (p <= info->d[0])
		{
			p = p + 2 * (info->d[1] - info->d[0]);
			y[0] += info->s[1];
		}
		if (x[0] == x[1])
			break ;
	}
}