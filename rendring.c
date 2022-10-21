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
void ray_render(t_minirt *minirt, t_mlx *mlx)
{
	// image
	const int image_width = 500;
	const int image_height = 500;
	float	aspect_ratio = (float )image_width / image_height;
	(void) minirt;
	(void) mlx;
	bool	hit;

	// camera
	float viewport_height  = 2.0;
	float viewport_width = aspect_ratio * viewport_height;
	float focal_e
	// Render
	t_sphere	sphere;
	t_ray		r;
	t_point 	Camera = {0, 0, -1};

	sphere.pos.x = 0;
	sphere.pos.y = 0;
	sphere.pos.z = 0;
	 /* Sphere radius */
	sphere.radius = 0.5;

	/* Direction of the ray */
	r.dir.x = 0;
	r.dir.y = 0;
	r.dir.z = 1;
	/* Start position of the ray, z coordinate */
	r.start.z = 0;
	int color;
	for (int y = image_height-1; y >= 0; --y) {
		r.start.y = y;
		for (int x = 0; x < image_width; ++x) {
			r.start.x = x;
			hit = intersectRaySphere(&r, &sphere);
			if (hit)
			{
//				color = (int)createRGB(255, 0, 0);
//				int X = (x / image_width);
//				int Y = ( y / image_width);
				my_mlx_pixel_put(mlx, X, Y, 0xFF0000);
			} else {
				int X = (x / image_width);
				int Y = (y / image_width);
//				my_mlx_pixel_put(mlx, X, Y, 0x000000);
			}
//			int ib = (int)(255.999 * b);
		}
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

