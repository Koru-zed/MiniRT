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




bool	intersectPlane(t_minirt *rt, t_ray ray, float *t)
{
	float p = v_dot(rt->Plane->normal, ray.direction);
	t_point resultOfSub = v_sub(rt->Plane->plane_point, ray.origin);
	*t = v_dot(resultOfSub, rt->Plane->normal) / p;
	if (*t > EPSILON)
	{
		rt->Plane->normal = rt->Plane->normal;
		rt->Plane->local_hit_point = v_adding(ray.origin, v_mul(*t, ray.direction));
		return true;
	}
	return false;
}

bool closest_sphere(t_minirt *rt, t_ray ray, float *t, COLOR *color)
{
	t_Sphere	*s;
	size_t	n_o;

	n_o = 0;
	s = rt->Sphere;
	float nearest = INFINITY;
	while (s)
	{
		if (intersectRaySphere(&ray, s, t) && *t < nearest)
		{
//			t_Sphere *closest = s;
			*color = (int)rgb(s->color);
			nearest = *t;
			n_o++;
		}
		s = s->next;
	}
	*t = nearest;
	if (!n_o)
		return false;
	return true;
}

bool closest_plane(t_minirt *rt, t_ray ray, float *t, COLOR *color)
{
	t_Plane 	*s;
	size_t	n_o;

	n_o = 0;
	float nearest = INFINITY;
	s = rt->Plane;
	while (s)
	{
		if (intersectPlane(rt, ray, t) && *t < nearest)
		{
//			t_Plane *closest = s;
			*color = rgb(s->color);
			nearest = *t;
			n_o++;
		}
		s = s->next;
	}
	*t = nearest;
	if (!n_o) {
		return false;
	}
	return true;
}

//t_Sphere closest_cylinder(t_minirt *rt, t_ray ray, float nearest, float *t)
//{
//
//}

void iterate_over_objects(t_minirt *rt, t_ray ray, float *t, COLOR *color)
{
	float t1;
	float t2 = INFINITY;
	COLOR color1;
	COLOR color2;

	if (closest_plane(rt, ray, &t1, &color1) || closest_sphere(rt, ray,&t2, &color2))
	{
		if (t1 > t2) {
			*color = color2;
			*t = t2;
		}
		else {
			*color = color1;
			*t = t1;
		}
	}
	else
	{
		*color = BLACK;
		*t = 0;
	}
}

void intersection_object(t_minirt *rt, t_ray ray, COLOR *color)
{
//	float t_nearest;
	float t;

//	t_nearest = INFINITY;INFINITY
	iterate_over_objects(rt, ray, &t, color);
}

void	ray_render(t_minirt *rt)
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
			ray = ray_generator(rt, x, y);
			iterate_over_objects(rt, ray, &t, &color);
			my_mlx_pixel_put(rt->Mlx, x, y, color);
			x++;
		}
		y++;
	}
}
