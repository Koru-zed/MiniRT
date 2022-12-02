#include "../Include/miniRT.h"

void	my_mlx_pixel_put(t_mlx *Mlx, int x, int y, int color)
{
	char	*dst;

	dst = Mlx->addr + (y * Mlx->line_length + x * (Mlx->bits_per_pixel >> 3));
	*(unsigned int*)dst = color;
}


void iterate_over_objects(t_minirt *rt, t_ray ray, double *t, t_hit **oHit) {
	double t1 = FLT_MAX;
	double t2 = FLT_MAX;
	t_hit *pHit;
	t_hit *pHit1;
	COLOR color1;
	COLOR color2;


	pHit = malloc(sizeof(t_hit));
	if (!pHit)
		exit(EXIT_FAILURE);
	pHit1 = malloc(sizeof(t_hit));
	if (!pHit1)
		exit(EXIT_FAILURE);
	bool isP = intersectPlane(rt, ray, &t1, &pHit);
	bool isS = intersectRaySphere(ray, rt, &t2, &pHit1);
	if (isP || isS) {
		if (t1 > t2) {
			free(pHit);
			pHit = NULL;
			*oHit = pHit1;
			*t = t2;
		} else if (t2 > t1) {
			free(pHit1);
			pHit1 = NULL;
			*oHit = pHit;
			*t = t1;
		} else {
			free(pHit);
			free(pHit1);
			pHit = NULL;
			pHit1 = NULL;
			(*oHit) = NULL;
			*t = FLT_MAX;
		}
	} else {
		free(pHit);
		free(pHit1);
		pHit = NULL;
		pHit1 = NULL;
		(*oHit) = NULL;
		*t = FLT_MAX;
	}
}
void	ray_render(t_minirt *mini)
{
	COLOR color;
	t_ray	ray;
	t_hit *hit = NULL;
	int y, x;
	y = 0;

	double t;
	// printf("camera_matrix\n");
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
			color = BLACK;
//			iterate_over_objects(mini, ray, &t, &hit);
//			if (hit) {
//				add_light(hit, mini, &color);
//				free(hit);
//			}
		color = BLACK;
			if (cylinder_int(mini, ray))
				color = 0x00FF00;
			my_mlx_pixel_put(mini->Mlx, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mini->Mlx->mlx, mini->Mlx->win, mini->Mlx->img, 0, 0);
}
