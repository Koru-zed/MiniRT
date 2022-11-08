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
	_cam->my_camera.left_corner = to_point(-2.0, 1.0, -1.0);
	_cam->my_camera.horizontal = to_point(4.0, 0.0, 0.0);
	_cam->my_camera.vertical = to_point(0.0, 2.0, 0.0);
	_cam->my_camera.origin = to_point(0.0, 0.0, 0.0);
	_cam->my_camera.direction = to_point(0.0, 0.0, 0.0);
}

void my_ray(t_ray *ray, float u, float v)
{
	t_point uh;
	t_point vv;

	uh = mul(u, ray->horizontal);
	vv = mul(v, ray->vertical);
	ray->direction = adding(uh, vv);
	ray->direction = adding(ray->direction, ray->left_corner);
}

void ray_render(t_minirt *minirt)
{
	// bool	hit;
	int x, y;
	float u, v;
	x = 0;
	y = 0;
	minirt->Sphere->radius = minirt->Sphere->diameter / 2;
	// minirt->Camera->my_camera = ft_calloc(1, sizeof(t_ray));
	// ray->dir.x = 0;//+ minirt->Camera->cordinates[0] * tan((double)minirt->Camera->fov/2);
	// ray->dir.y = 0;//+ minirt->Camera->cordinates[1] * tan((double)minirt->Camera->fov/2);
	// ray->dir.z = -1.0;
	// // float t;
	// ray->start.z = 2.0;
	t_point col, u_di, vec1, vec2;
	vec1.x = 1.0;
	vec1.y = 1.0;
	vec1.z = 1.0;
	vec2.x = 0.5;
	vec2.y = 0.7;
	vec2.z = 1.0;
	my_camera(minirt->Camera);
	// ft_get_camera(minirt);
	while (y < 540)
	{
		while (x < 720)
		{
			u = x / 720;
			v = y / 540;
			my_ray(&minirt->Camera->my_camera, u, v);
			u_di = normalizing(minirt->Camera->my_camera.direction);
			minirt->Camera->my_camera.t = 0.5 *(u_di.y + 1.0);
			vec1 = mul((1.0 - minirt->Camera->my_camera.t), vec1);
			vec2 = mul(minirt->Camera->my_camera.t, vec2);
			col = adding(vec1, vec2);
			// hit = intersectRaySphere(ray, minirt->Sphere, &t);
			// if (hit)
			int a = createRGB(col.x, col.y, col.z);
			if (a)
				printf("color[%d]\n", a);
			my_mlx_pixel_put(minirt->Mlx, x, y, a);
			// else
			// 	my_mlx_pixel_put(minirt->Mlx, x, y, 0x000033 );
			x++;
		}
		y++;
		x = 0;
	}
}

//plane
bool Plane_intersect(t_Plane *_plane)
{
	// First, check if we intersect
	float dDotN = dot(.co, normal);

	if (dDotN == 0.0f)
	{
		// We just assume the ray is not embedded in the plane
		return false;
	}

	// Find point of intersection
	float t = dot(position - intersection.ray.origin, normal)
		/ dDotN;

	if (t <= RAY_T_MIN || t >= intersection.t)
	{
		// Outside relevant range
		return false;
	}

	intersection.t = t;
	intersection.pShape = this;
	intersection.color = color;

	return true;
}


// void ray_render(t_minirt *minirt)
// {

// 	t_ray	*ray;
// 	bool	hit;
// 	int x, y;

// 	x = 0;
// 	y = 0;
// 	minirt->Sphere->radius = minirt->Sphere->diameter / 2;
// 	ray = ft_calloc(1, sizeof(t_ray));
// 	ray->dir.x = minirt->Camera->cordinates.x;
// 	ray->dir.y = minirt->Camera->cordinates.y;
// 	ray->dir.z = minirt->Camera->cordinates.z;
// 	int color;
// //	float t;
// //	get_camera_location();
// 	// printf("mag %d  && normaliz == %d\n", length_squared(ray->dir))
// 	ray->start.z = 2.0f;
// 	while (y < 540)
// 	{
// 		ray->start.y = (float)y;
// 		while (x < 720)
// 		{
// 			ray->start.x = (float )x;
// 			hit = intersectRaySphere(ray, minirt->Sphere, &color);
// 			if (hit)
// 				my_mlx_pixel_put(minirt->Mlx, x, y, color);
// 			else
// 			{
// //				t_point unit = unit_vector(ray->dir);
// //				float  f = 0.5f*(unit.y + 1.0f);
// //				int color = ((1.0-f)*createRGB(1.0, 1.0, 1.0) *  f * createRGB(0.5, 0.7, 1.0));
// 				my_mlx_pixel_put(minirt->Mlx, x, y, 0xFF0000);
// 			}
// 			x++;
// 		}
// 		y++;
// 		x = 0;
// 	}
// }
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

