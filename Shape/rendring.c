#include "../Include/miniRT.h"

void	my_mlx_pixel_put(t_mlx *Mlx, int x, int y, int color)
{
	char	*dst;

	dst = Mlx->addr + (y * Mlx->line_length + x * (Mlx->bits_per_pixel >> 3));
	*(unsigned int*)dst = color;
}


/*void iterate_over_objects(t_minirt *rt, t_ray ray, float *t, COLOR *color)
{
	float t1 = FLT_MAX;
	float t2 = FLT_MAX;
	COLOR color1;
	COLOR color2;
	
	bool isP = intersectPlane(rt, ray, &t1, &color1);
	bool isS = intersectRaySphere(ray, rt, &t2, &color2);
	*color = BLACK;
	if (isP || isS) {
		if (t1 > t2 && t2 > 0) {
			*color = color2;
			*t = t2;
		}
		else if (t2 > t1 && t1 > 0) {
			*color = color1;
			*t = t1;
		}
		else {
			*color = BLACK;
			*t = 0;
		}
	}

}*/


void	ray_render(t_minirt *mini)
{
	COLOR color;
	t_ray	ray;
	int y, x;
	t_hit	*pHit;
	y = 0;

	float t;
	// printf("camera_matrix\n");
	pHit = malloc(sizeof(t_hit));
	if (!pHit)
		exit(EXIT_FAILURE);
	camera_matrix(mini->Camera);
	print_matrix(mini->Camera->matrix);
	// printf("***********************************************\n");
	// print_matrix(mini->Camera->matrix);

	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ray = ray_generator(mini, x, y);
//			iterate_over_objects(mini, ray, &t, &color);
			color = BLACK;
			if (intersectRaySphere(ray, mini, &t, &pHit))
				add_light(pHit, mini, &color);
			my_mlx_pixel_put(mini->Mlx, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mini->Mlx->mlx, mini->Mlx->win, mini->Mlx->img, 0, 0);
}
