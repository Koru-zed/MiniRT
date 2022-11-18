#include "Include/miniRT.h"



/*
 * Let's make:
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


bool	intersectPlane(t_minirt *rt, t_ray ray, float *t, int *color)
{
	float tmin;
	float hd;
	t_Plane *tPlane;
	t_intersect closestPlane;


	hd = EPSILON;
	tPlane = rt->Plane;
	closestPlane.tmin = FLT_MAX;
	while (tPlane)
	{
		float p = v_dot(tPlane->normal, ray.direction);
		t_point resultOfSub = v_sub(tPlane->plane_point, ray.origin);
		tmin = v_dot(resultOfSub, tPlane->normal) / p;

		if (tmin > EPSILON)
		{
			// true tmin = 1.0  true 0.5
			if (closestPlane.tmin > tmin) {
				closestPlane.closestPoint = tPlane->plane_point;
				closestPlane.color = tPlane->color;
				closestPlane.tmin = tmin;
			}
		}
		tPlane = tPlane->next;
	}
	if (closestPlane.tmin == FLT_MAX)
	{
		*t = FLT_MAX;
		return false;
	}
	*t = closestPlane.tmin;
//	rt->Plane->normal = closestPlane.normal;
//	rt->Plane->local_hit_point = v_adding(ray.origin, v_mul(hd, ray.direction));
	*color = rgb(closestPlane.color);
/*	if (*t > EPSILON)
	{
		rt->Plane->normal = rt->Plane->normal;
		rt->Plane->local_hit_point = v_adding(ray.origin, v_mul(*t, ray.direction));
		return true;
	}*/
	return true;
}


void iterate_over_objects(t_minirt *rt, t_ray ray, float *t, COLOR *color)
{
	float t1;
	float t2;
	COLOR color1;
	COLOR color2;
	bool isP = intersectPlane(rt, ray, &t1, &color1);
	bool isS = intersectRaySphere(ray, rt, &t2, &color2);
	*color = BLACK;
	if (isP || isS) {
		if (t1 > t2 && isS) {
			*color = color2;
			*t = t2;
		}
		else if (t2 > t1 && isP) {
			*color = color1;
			*t = t1;
		}
		else {
			*color = BLACK;
			*t = 0;
		}
	}

}


void	ray_render(t_minirt *rt)
{
	t_ray	ray;
	int y, x;
	y = 0;

//	float t;
	int fd;
	fd = open("debug.txt", O_RDWR | O_TRUNC);
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ray = ray_generator(rt, x, y);
//			iterate_over_objects(rt, ray, &t, &color);
			ft_print_vector(ray.direction, fd);
			if (cylinder_intersection(rt, &ray, fd))
				my_mlx_pixel_put(rt->Mlx, x, y, 0xE4D00A);
			x++;
		}
		y++;
	}
}
