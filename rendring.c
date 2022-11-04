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
void	add_cord(int i, int j, t_matrix **m, t_point p)
{
	(*m)[j][i] = p.x;
	(*m)[j][i] = p.y;
	(*m)[j][i] = p.z;
}
void	add_neg_cord(int j, t_matrix **m, t_point p)
{
	(*m)[j][3] = -p.x;
	(*m)[j][3] = -p.y;
	(*m)[j][3] = -p.z;
}

/*
  * we need FOV (field of view)
 * and aspect ratio = w/h == w =  width / height

 *  field of view dependes of sensor size and
 *  the equation is FOV = 2 tan^-1 (h/2f)
 */

t_matrix	*viewport(int x, int y, int w, int h)
{
	t_matrix	*m = creat_matrix(4);
	m[0][3] = x+w/2.f;
	m[1][3] = y+h/2.f;
	m[2][3] = depth/2.f;

	m[0][0] = w/2.f;
	m[1][1] = h/2.f;
	m[2][2] = depth/2.f;
	return m;
}

t_matrix	*look_at(t_point eye, t_point center, t_point up)
{
	int i;

	i = 0;
	t_point	z = normalizing(sub(eye, center));
	t_point	x = normalizing(cross(up, z));
	t_point	y = normalizing(cross(z, x));
	t_matrix*	Minv = creat_matrix(3);
	t_matrix*	Tr = creat_matrix(3);
	while (i < Minv->col)
	{
		add_cord(i, 0,&Minv, x);
		add_cord(i, 1,&Minv, y);
		add_cord(i, 2,&Minv, z);
		add_neg_cord(i, &Tr, eye);
		i++;
	}
	t_matrix	*modelView = matrix_multiplication(Minv, Tr);
	return modelView;
}
/*
 *  t, represent the length of the closest intersection.
 */
void ray_render(t_minirt *minirt)
{

	t_ray	*ray;
	bool	hit;
	int x, y;

	x = 0;
	y = 0;
	minirt->Sphere->radius = minirt->Sphere->diameter / 2;
	ray = ft_calloc(1, sizeof(t_ray));
	ray->dir.x = minirt->Camera->cordinates[0];
	ray->dir.y = minirt->Camera->cordinates[1];
	ray->dir.z = minirt->Camera->cordinates[2];
	int color;
//	float t;
//	get_camera_location();
	printf("mag %d  && normaliz == %d\n", length_squared(ray->dir))
	ray->start.z = 2.0f;
	while (y < 540)
	{
		ray->start.y = (float)y;
		while (x < 720)
		{
			ray->start.x = (float )x;
			hit = intersectRaySphere(ray, minirt->Sphere, &color);
			if (hit)
				my_mlx_pixel_put(minirt->Mlx, x, y, color);
			else
			{
//				t_point unit = unit_vector(ray->dir);
//				float  f = 0.5f*(unit.y + 1.0f);
//				int color = ((1.0-f)*createRGB(1.0, 1.0, 1.0) *  f * createRGB(0.5, 0.7, 1.0));
				my_mlx_pixel_put(minirt->Mlx, x, y, 0xFF0000);
			}
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

