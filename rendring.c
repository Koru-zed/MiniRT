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


t_point ray_color(t_ray *r, t_Sphere *s)
{
	float	t = intersect(r, s);
	if (t > 0.0)
	{
		t_point p = {0, 0, -1, 0};
		t_point n = unit_vector(sub(at(t, r), p));
		t_point color = {n.x + 1, n.y + 1, n.z + 1, 0};
		t_point re = mul(0.5f - t, color);
		return re;
	}
	t_point n = unit_vector(r->dir);
	t_point color1 = {1.0f, 1.0f, 1.0f, 0};
	t_point color2 = {0.5f, 0.7f, 1.0f, 0};
	t = 0.5f * (n.y + 1.0f);
	return adding(mul(1.0f - t, color1), mul(t, color2));
}

t_minirt *perspective_camera(t_point origin, t_point target, t_point up_guide, t_minirt *rt, float aspectRatio)
{
	rt->Camera->forward = normalizing(sub(target, origin));
	rt->Camera->right = normalizing(cross(rt->Camera->forward, up_guide));
	rt->Camera->up = cross(rt->Camera->right, rt->Camera->forward);
	rt->Camera->h = tan((double ) rt->Camera->fov);
	rt->Camera->w = rt->Camera->h * aspectRatio;
	return rt;
}

t_ray	init_ray(t_point origin, t_point dir)
{
	t_ray	r;

	r.origin = origin;
	r.dir = dir;
 	return r;
}

t_ray	makeRay(t_minirt *rt, t_point p)
{
	// * dir = forward + ( (p.u * w) * right ) + ( (p.v * h) * up )
	float tmp = rt->Camera->w * p.x;
	t_point tmp1 = mul(tmp , rt->Camera->right);
	float tmp2 = rt->Camera->h * p.y;
	t_point tmp3 = mul(tmp2, rt->Camera->up);

	t_point s = adding(rt->Camera->forward, tmp1);
	t_point dir = adding(s, tmp3);
	return init_ray(convert_to_point(rt->Camera->cordinates), normalizing(dir));
}

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

bool	intersectPlane(t_minirt *rt, t_point phat, t_ray ray, float *t)
{
	t_point normal = convert_to_point(rt->Plane->orientation); // tmp for now
	float p = dot(normal, ray.dir);
	t_point resultOfSub = sub(phat, ray.origin);
	*t = dot(resultOfSub, normal) / p;
	if (*t > EPSILON)
	{
		rt->Plane->normal = normal;
		rt->Plane->local_hit_point = adding(ray.origin, mul(*t, ray.dir));
		return true;
	}
	return false;
}

void	ray_render(t_minirt *rt)
{
	t_ray r;

	r.origin.x = 0;
	r.origin.y = 0;
	r.origin.z = -1;
	float t;
	t_point p = convert_to_point(rt->Plane->cordinates);
	for (int i = 0; i < 540; ++i) {
		r.origin.y = i;
		for (int j = 0; j < 720; ++j) {
			r.origin.x = 0;
			if (intersectPlane(rt, p, r, &t))
			{
				my_mlx_pixel_put(rt->Mlx, j, i, 0xFFFFFF);
			}
			else
				my_mlx_pixel_put(rt->Mlx, j, i, 0x00FF00);
		}
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

