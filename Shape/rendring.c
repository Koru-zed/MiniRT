#include "../Include/miniRT.h"

void	my_mlx_pixel_put(t_mlx *Mlx, int x, int y, int color)
{
	char	*dst;

	dst = Mlx->addr + (y * Mlx->line_length + x * (Mlx->bits_per_pixel >> 3));
	*(unsigned int*)dst = color;
}


// void iterate_over_objects(t_minirt *rt, t_ray ray, double *t, COLOR *color)
// {
// 	double t1 = FLT_MAX;
// 	double t2 = FLT_MAX;
// 	COLOR color1;
// 	COLOR color2;
	
// 	*t = 0;
// 	*color = BLACK;
// 	bool isP = intersectPlane(rt, ray, &t1, &color1);
// 	bool isS = intersectRaySphere(ray, rt, &t2, &color2);
// 	if (isP && isS) {
// 		if (t1 > t2 && t2 > EPSILON)
// 		{
// 			*color = color2;
// 			*t = t2;
// 		}
// 		else if (t1 > t2 && t1 > EPSILON)
// 		{
// 			*color = color1;
// 			*t = t1;
// 		}
// 		else if (t2 > t1 && t1 > EPSILON)
// 		{
// 			*color = color1;
// 			*t = t1;
// 		}
// 		else if (t2 > t1 && t2 > EPSILON)
// 		{
//             *color = color2;
// 			*t = t2;
// 		}
// 	}
// 	else if (isP && t1 > EPSILON)
//     {
//         *color = color1;
// 		*t = t1;
// 	}
// 	else if (isS && t2 > EPSILON)
//     {
//         *color = color2;
// 		*t = t2;
// 	}
// }

void iterate_over_objects(t_minirt *rt, t_ray ray, double *t, COLOR *Color)
{
	int i;
	double t_t[3];
	bool is[3];
	COLOR color[3];
	
	i = -1;
	*t = FLT_MAX;
	*Color = BLACK;
	t_t[0] = FLT_MAX;
	t_t[1] = FLT_MAX;
	t_t[2] = FLT_MAX;
	is[PL] = intersectPlane(rt, ray, &t_t[PL], &color[PL]);
	is[SP] = intersectRaySphere(ray, rt, &t_t[SP], &color[SP]);
	is[CY] = cylinder_intersection(rt, ray, &t_t[CY], &color[CY]);
	while (++i < 3)
	{
		if (is[i] && t_t[i] > EPSILON && t_t[i] < *t)
		{
			*t = t_t[i];
			*Color = color[i];
			if (i == PL)
				rt->Mlx->obj.object = _PLANE;
			else if (i == SP)
				rt->Mlx->obj.object = _SEPHER;
			else if (i == CY)
				rt->Mlx->obj.object = _CYLINDER;
		}
	}
}


void intersection_over_objects(t_minirt *rt, t_ray ray)
{
	
	int i;
	double t[3];
	bool is[3];
	COLOR color[3];

	i = -1;
	t[0] = FLT_MAX;
	t[1] = FLT_MAX;
	t[2] = FLT_MAX;
	is[PL] = intersectPlane(rt, ray, &t[PL], &color[PL]);
	is[SP] = intersectRaySphere(ray, rt, &t[SP], &color[SP]);
	is[CY] = cylinder_intersection(rt, ray, &t[CY], &color[CY]);
	while (++i < 3)
	{
		if (is[i] && t[i] > EPSILON && t[i] < *t)
		{
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
	int y, x;
	y = 0;

	double t;
	// printf("camera_matrix\n");
	camera_matrix(mini->Camera);
	// print_matrix(mini->Camera->matrix);
	// printf("***********************************************\n");
	// print_matrix(mini->Camera->matrix);
	// printf("before rendring -> index [%d]\n", mini->Mlx->obj.index);

	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ray = ray_generator(mini, x, y);
			iterate_over_objects(mini, ray, &t, &color);
			my_mlx_pixel_put(mini->Mlx, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mini->Mlx->mlx, mini->Mlx->win, mini->Mlx->img, 0, 0);
}
