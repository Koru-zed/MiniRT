#include "../Include/miniRT.h"

void	my_mlx_pixel_put(t_mlx *Mlx, int x, int y, int color)
{
	char	*dst;

	dst = Mlx->addr + (y * Mlx->line_length + x * (Mlx->bits_per_pixel >> 3));
	*(unsigned int*)dst = color;
}

/*
 * Let's make:make
		* $ A = \vec d.\vec d $
		* $ B = 2\vec d.(\vec p_0 - \vec c) $
		* $ C = (\vec p_0 - \vec c).(\vec p_0 - \vec c) - r^2 $
		*
		  *  We need a vector representing the distance between the origin of
 				 * the ray and the position of the circle. < dist >
*/


//t_sphere	init_ray(t_sphere s)
//{
///* Position the sphere */
//	s.pos.x = 200;
//	s.pos.y = 200;
//	s.pos.z = 100;
//	/* Sphere radius */
//	s.radius = 100;
//	return s;
//}

//void	add_cord(int i, int j, t_matrix **m, t_point p)
//{
//	(*m)[j][i] = p.x;
//	(*m)[j][i] = p.y;
//	(*m)[j][i] = p.z;
//}
//void	add_neg_cord(int j, t_matrix **m, t_point p)
//{
//	(*m)[j][3] = -p.x;
//	(*m)[j][3] = -p.y;
//	(*m)[j][3] = -p.z;
//}

/*
  * we need FOV (field of view)
 * and aspect ratio = w/h == w =  width / height

 *  field of view dependes of sensor size and
 *  the equation is FOV = 2 tan^-1 (h/2f)
 */





//bool closest_plane(t_minirt *rt, t_ray ray, float *t, COLOR *color)
//{
//	t_Plane 	*s;
//	size_t	n_o;
//
//	n_o = 0;
//	float nearest = INFINITY;
//	s = rt->Plane;
//	while (s)
//	{
//		if (intersectPlane(rt, ray, t) && *t < nearest)
//		{
////			t_Plane *closest = s;
//			*color = rgb(s->color);
//			nearest = *t;
//			n_o++;
//		}
//		s = s->next;
//	}
//	*t = nearest;
//	if (!n_o) {
//		return false;
//	}
//	return true;
//}

//t_Sphere closest_cylinder(t_minirt *rt, t_ray ray, float nearest, float *t)
//{
//
//}

void iterate_over_objects(t_minirt *rt, t_ray ray, float *t, COLOR *color)
{
	float t1 = FLT_MAX;
	float t2 = FLT_MAX;
	COLOR color1;
	COLOR color2;
	
	bool isP = intersectPlane(rt, ray, &t1, &color1);
	bool isS = intersectRaySphere(ray, rt, &t2, &color2);
	*color = BLACK;
	if (isP || isS) {
		if (t1 > t2) {
			*color = color2;
			*t = t2;
		}
		else if (t2 > t1) {
			*color = color1;
			*t = t1;
		}
		else {
			*color = BLACK;
			*t = 0;
		}
	}

}


void	ray_render(t_minirt *mini)
{
	COLOR color;
	t_ray	ray;
	int y, x;
	y = 0;

	float t;
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
