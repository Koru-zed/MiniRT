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
		  *  We need a vector representing the distance between the start of
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


/*
 *  t, represent the length of the closest intersection.
 */

void my_camera(t_Camera *_cam)
{
	_cam->my_camera.left_corner = to_point(-2.0, -1.0, 0.0);
	_cam->my_camera.horizontal = to_point(4.0, 0.0, 0.0);
	_cam->my_camera.vertical = to_point(0.0, 2.0, 0.0);
	_cam->my_camera.origin = to_point(0.0, 0.0, 0.0);
	_cam->my_camera.direction = to_point(0.0, 0.0, 0.0);
}

void my_ray(t_ray *ray, float u, float v)
{
	t_ray uh;
	t_ray vv;

	uh = mul(u, ray->horizontal);
	vv = mul(v, ray->vertical);
	ray->direction = adding(uh, vv);
	ray->direction = adding(ray->direction, ray->left_corner);
}

void ray_render(t_minirt *minirt)
{
	bool	hit;
	int x, y;
	float u, v;
	x = 0;
	y = 0;
	// minirt->Sphere->radius = minirt->Sphere->diameter / 2;
	minirt->Camera->my_camera = ft_calloc(1, sizeof(t_ray));
	// ray->dir.x = 0;//+ minirt->Camera->cordinates[0] * tan((double)minirt->Camera->fov/2);
	// ray->dir.y = 0;//+ minirt->Camera->cordinates[1] * tan((double)minirt->Camera->fov/2);
	// ray->dir.z = -1.0;
	// // float t;
	// ray->start.z = 2.0;
	ray_camera(minirt->Camera);
	ft_get_camera(minirt);
	while (y < 540)
	{
		while (x < 720)
		{
			u = x / 720;
			v = y / 540;
			my_ray(minirt->Camera, u, v);
			// hit = intersectRaySphere(ray, minirt->Sphere, &t);
			// if (hit)
			// 	my_mlx_pixel_put(minirt->Mlx, x, y, 0xFFFF00);
			// else
			// 	my_mlx_pixel_put(minirt->Mlx, x, y, 0x000033 );
			x++;
		}
		y++;
		x = 0;
	}
}
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

