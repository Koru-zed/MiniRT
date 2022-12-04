#include "../Include/miniRT.h"

void	my_mlx_pixel_put(t_mlx *Mlx, int x, int y, int color)
{
	char	*dst;

	dst = Mlx->addr + (y * Mlx->line_length + x * (Mlx->bits_per_pixel >> 3));
	*(unsigned int*)dst = color;
}


void iterate_over_objects(t_minirt *rt, t_ray ray, double *t,  t_hit **oHit)
{
	int i;
	double t_t[3];
	t_hit *pHit = malloc(sizeof(t_hit) * 3);
	bool is[3];

	i = -1;
	*t = FLT_MAX;
	*oHit = NULL;
	t_t[0] = FLT_MAX;
	t_t[1] = FLT_MAX;
	t_t[2] = FLT_MAX;
	is[PL] = intersectPlane(rt, ray, &t_t[PL], &pHit[PL]);
	is[SP] = intersectRaySphere(ray, rt, &t_t[SP], &pHit[SP]);
	is[CY] = cylinder_intersection(rt, ray, &t_t[CY], &pHit[CY]);
	while (++i < 3)
	{
		if (is[i] && t_t[i] > EPSILON && t_t[i] < *t)
		{
			*t = t_t[i];
			*oHit = &pHit[i];
		}
	}
}


void intersection_over_objects(t_minirt *rt, t_ray ray)
{

	int i;
	double t;
	double t_t[3];
	t_hit pHit[3];
	bool is[3];

	i = -1;
	t = FLT_MAX;
	t_t[0] = FLT_MAX;
	t_t[1] = FLT_MAX;
	t_t[2] = FLT_MAX;
	is[PL] = intersectPlane(rt, ray, &t_t[PL], &pHit[PL]);
	is[SP] = intersectRaySphere(ray, rt, &t_t[SP], &pHit[SP]);
	is[CY] = cylinder_intersection(rt, ray, &t_t[CY], &pHit[CY]);
	while (++i < 3)
	{
		if (is[i] && t_t[i] > EPSILON && t_t[i] < t)
		{
			t = t_t[i];
			if (i == PL)
				rt->Mlx->obj.object = _PLANE;
			else if (i == SP)
				rt->Mlx->obj.object = _SEPHER;
			else if (i == CY)
				rt->Mlx->obj.object = _CYLINDER;
		}
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
	// print_matrix(mini->Camera->matrix);
	// printf("***********************************************\n");
	// print_matrix(mini->Camera->matrix);

	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ray = ray_generator(mini, x, y);
			color = BLACK;
			iterate_over_objects(mini, ray, &t, &hit);
			if (hit) {
				add_light(hit, mini, &color);
				// if (mini->Mlx->obj.object == _CYLINDER)
				// {
				// 	color = rgb(hit->obj_color);
				// }
			}
			my_mlx_pixel_put(mini->Mlx, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mini->Mlx->mlx, mini->Mlx->win, mini->Mlx->img, 0, 0);
}
