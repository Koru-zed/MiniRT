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

void iterate_over_objects(t_minirt *rt, t_ray ray, double *t, COLOR *color)
{
	double t1 = FLT_MAX;
	double t2 = FLT_MAX;
	double t3 = FLT_MAX;
	COLOR color1;
	COLOR color2;
	COLOR color3;
	
	*t = 0;
	*color = BLACK;
	bool isP = intersectPlane(rt, ray, &t1, &color1);
	bool isS = intersectRaySphere(ray, rt, &t2, &color2);
	bool isC = cylinder_intersection(rt, ray, &t3, &color3);
	if (isP || isS || isC) {
		if (t1 > t2 && t2 < t3 && t2 > EPSILON)
		{
			*color = color2;
			*t = t2; 
		}
		else if (t2 > t1 && t1 < t3 && t1 > EPSILON)
		{
			*color = color2;
			*t = t1; 
		}
		else if (t2 > t3 && t3 < t1 && t3 > EPSILON)
		{
			*color = color3;
			*t = t3; 
		}
	}
	// printf("t -> [%f]\n", *t);
}
void intersection_over_objects(t_minirt *rt, t_ray ray)
{
	double t1 = FLT_MAX;
	double t2 = FLT_MAX;
	double t3 = FLT_MAX;
	COLOR color1;
	COLOR color2;
	COLOR color3;
	
	bool isP = intersectPlane(rt, ray, &t1, &color1);
	bool isS = intersectRaySphere(ray, rt, &t2, &color2);
	bool isC = cylinder_intersection(rt, ray, &t3, &color3);
	if (isP || isS || isC) {
		if (t1 > t2 && t2 < t3 && t2 < EPSILON)
			rt->Mlx->obj.object =  _SEPHER;
		else if (t2 > t1 && t1 < t3 && t1 < EPSILON)
			rt->Mlx->obj.object =  _PLANE;
		else if (t2 > t3 && t3 < t1 && t3 < EPSILON)
			rt->Mlx->obj.object =  _CYLINDER;
	}
	else 
		rt->Mlx->obj.object = 0;
}

// void intersection_over_objects(t_minirt *rt, t_ray ray)
// {
// 	double t1 = FLT_MAX;
// 	double t2 = FLT_MAX;
// 	double t3 = FLT_MAX;
// 	COLOR color1;
// 	COLOR color2;
// 	COLOR color3;
	
// 	bool isP = intersectPlane(rt, ray, &t1, &color1);
// 	bool isS = intersectRaySphere(ray, rt, &t2, &color2);
// 	bool isC = cylinder_intersection(rt, ray, &t3, &color1);
// 	if (isP && isS) {
// 		if (t1 > t2 && t2 > EPSILON)
// 			rt->Mlx->obj.object =  _SEPHER;
// 		else if (t1 > t2 && t1 > EPSILON)
// 			rt->Mlx->obj.object =  _PLANE;
// 		else if (t2 > t1 && t1 > EPSILON)
// 			rt->Mlx->obj.object =  _PLANE;
// 		else if (t2 > t1 && t2 > EPSILON)
// 			rt->Mlx->obj.object =  _SEPHER;
// 	}
// 	else if (isP && t1 > EPSILON)
// 		rt->Mlx->obj.object =  _PLANE;
// 	else if (isS && t2 > EPSILON)
// 		rt->Mlx->obj.object =  _SEPHER;
// 	else 
// 		rt->Mlx->obj.object = 0;
// }

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
