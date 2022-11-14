#include "Include/miniRT.h"

/*void	sphere(t_mlx mlx) {
	const int image_width = 256;
	const int image_height = 256;
	for (int j = image_height - 1; j >= 0; --j) {
		for (int i = 0; i < image_width; ++i) {
			double r = (double) i / (image_width - 1);
			double g = (double) j / (image_height - 1);
			double b = 0.25;
			int color = (int) createRGB(r, g, b);
			my_mlx_pixel_put(&mlx, i, j, color);
		}
	}
}*/

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

//ft_matrix	*viewport(int x, int y, int w, int h)
//{
//	t_matrix	*m = creat_matrix(4);
//	m[0][3] = x+w/2.f;
//	m[1][3] = y+h/2.f;
//	m[2][3] = depth/2.f;
//
//	m[0][0] = w/2.f;
//	m[1][1] = h/2.f;
//	m[2][2] = depth/2.f;
//	return m;
//}


//t_point ray_color(t_ray *r, t_Sphere *s)
//{
//	float	t = intersect(r, s);
//	if (t > 0.0)
//	{
//		t_point p = {0, 0, -1, 0};
//		t_point n = unit_vector(sub(at(t, r), p));
//		t_point color = {n.x + 1, n.y + 1, n.z + 1, 0};
//		t_point re = mul(0.5f - t, color);
//		return re;
//	}
//	t_point n = unit_vector(r->dir);
//	t_point color1 = {1.0f, 1.0f, 1.0f, 0};
//	t_point color2 = {0.5f, 0.7f, 1.0f, 0};
//	t = 0.5f * (n.y + 1.0f);
//	return adding(mul(1.0f - t, color1), mul(t, color2));
//}

//t_matrix	*look_at(t_point eye, t_point center, t_point up)
//{
//	int i;
//
//	i = 0;
//	t_point	z = normalizing(sub(eye, center));
//	t_point	x = normalizing(cross(up, z));
//	t_point	y = normalizing(cross(z, x));
//	t_matrix*	Minv = creat_matrix(3);
//	t_matrix*	Tr = creat_matrix(3);
//	while (i < Minv->col)
//	{
//		add_cord(i, 0,&Minv, x);
//		add_cord(i, 1,&Minv, y);
//		add_cord(i, 2,&Minv, z);
//		add_neg_cord(i, &Tr, eye);
//		i++;
//	}
//	t_matrix	*modelView = matrix_multiplication(Minv, Tr);
//	return modelView;
//}
//



bool	intersectPlane(t_minirt *rt, t_ray ray, float *t)
{
	//t_point normal = convert_to_point(rt->Plane.); // tmp for now
	float p = v_dot(rt->Plane->normal, ray.direction);
//	if (fabsf(p) > EPSILON)
//		return false;
	t_point resultOfSub = v_sub(rt->Plane->plane_point, ray.origin);
	*t = v_dot(resultOfSub, rt->Plane->normal) / p;
	if (*t > EPSILON)
	{
//		printf("true\n");
		rt->Plane->normal = rt->Plane->normal;
		rt->Plane->local_hit_point = v_adding(ray.origin, v_mul(*t, ray.direction));
		return true;
	}
//	printf("false\n");
	return false;
}

bool closest_sphere(t_minirt *rt, t_ray ray, float nearest, float *t)
{
	t_Sphere	*s;
	size_t	n_o;

	n_o = 0;
	s = rt->Sphere;
	while (s)
	{
		if (intersectRaySphere(&ray, s, t) && *t < nearest)
		{
			t_Sphere *closest = s;
			nearest = *t;
		}
		s = s->next;
	}
	return true;
}

t_Sphere closest_plane(t_minirt *rt, t_ray ray, float nearest, float *t)
{

}

//t_Sphere closest_cylinder(t_minirt *rt, t_ray ray, float nearest, float *t)
//{
//
//}

bool iterate_over_objects(t_minirt *rt, t_ray ray, float nearest, float *t)
{

}

bool intersection_object(t_minirt *rt, t_ray ray, COLOR *color)
{
	float t_nearest;
	float t;

	t_nearest = INFINITY;
	*color  = BLACK;
	iterate_over_objects(rt, ray, t_nearest, &t);
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
			intersection_object(rt, ray, &color);
			my_mlx_pixel_put(rt->Mlx, x, y, color);
			x++;
		}
		y++;
	}
}
/*
 *  t, represent the length of the closest intersection.

void ray_render(t_minirt *minirt)
{

	t_ray	*ray;
	__attribute__((unused)) bool	hit;
	int x, y;

	x = 0;
	y = 0;
	minirt->Sphere->radius = minirt->Sphere->diameter / 2;
	ray = ft_calloc(1, sizeof(t_ray));
	ray->origin.x = 0.0f;
	ray->origin.y = 0.0f;
	ray->origin.z = 0.0f;
	t_point lower_left_corner = {-2.0f, -1.0f, -1.f, 0};
	t_point horizontal = {4.0f, 0.0f, 0.0f, 0};
	t_point vertical = {0.0f, 2.0f, 0.0f, 0};
//	t_point origin = {0.0f, 0.0f, 0.0f, 0};0/
	int color;
//	float t;
//	get_camera_location();
//	printf("mag %f  && normaliz == %d\n", length_squared(ray->dir))
	ray->origin.z = 2.0f;
//	perspective_camera()
	y = 540 - 1;
	while (y)
	{
//		ray->origin.y = (float)y;
		x = 720 - 1;
		while (x)
		{
			float u = (float )x / 720;
			float v = (float )y / 540;
			ray->dir = adding(adding(lower_left_corner, mul(u, horizontal)), mul(v, vertical));
//			ray->origin.x = (float )x;
//			float xhat = (2.0f*(float )x / 720 - 1.0f);
//			float yhat = (-2.0f*(float )y / 540 + 1.0f);
//			t_point p = {xhat, yhat, 0, 0};
//			t_ray ray1 = makeRay(minirt, p);
//			hit = intersectRaySphere(&ray1, minirt->Sphere, &color);
			t_point col = ray_color(ray, minirt->Sphere);
			color = createRGB(col.x, col.y, col.z);
			my_mlx_pixel_put(minirt->Mlx, x, y, color);
//			if (hit)
//				my_mlx_pixel_put(minirt->Mlx, x, y, 0x00FF00);
//			else
//			{
//				t_point unit = unit_vector(ray->dir);
//				float  f = 0.5f*(unit.y + 1.0f);
//				int color = ((1.0-f)*createRGB(1.0, 1.0, 1.0) *  f * createRGB(0.5, 0.7, 1.0));
//				my_mlx_pixel_put(minirt->Mlx, x, y, 0xFF0000);
//			}
			x--;
		}
		y--;
	}
}*/
/*




bool	ray_interesct(const t_point origin, const t_point dir, float *t, t_point center, float r)
{
	t_point	L;
	float	tca;
	float	d2;
	float	thc;
	float	t0;

	L = sub(center, origin);
	tca = mul(L, dir);
	d2 = mul(L, L) - tca * tca;
	thc = sqrtf(r * r - d2);
	*t = tca - thc;
	t0 = tca + thc;
	if (*t < 0)
		*t = t0;
	if (*t < 0)
		return false;
	return true;
}

void	sphere()
{
	float	radius;
	t_vector center;



}*/

