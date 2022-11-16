#include "../Include/miniRT.h"

/*
 *  ∗ identifier: cy
	* cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255
	* ∗ x,y,z coordinates: 50.0,0.0,20.6
	* ∗ 3d normalized orientation vector. In range [-1,1] for each x,y,z axis: 0.0,0.0,1.0
	* ∗ the cylinder diameter: 14.2
	* ∗ the cylinder height: 21.42
	* ∗ R,G,B colors in range [0,255]: 10, 0, 255
 */
//bool	cylinder_intersection(t_minirt *rt, t_ray *ray)
//{
//	float r = rt->Cylinder->diameter / 2;
//	float a = powf(ray->dir.x, 2.0) + powf(ray->dir.z, 2.0);
//	float b = 2.0 * ray->origin.x * ray->dir.x + 2.0 * ray->origin.z * ray->dir.z;
//	float c = powf(ray->origin.x, 2.0) + powf(ray->origin.z, 2) - r; // they put 1 i don't know why
//	float disc = powf(b, 2) - 4 * a * c;
//	// ? if the disc is equals to 0  the ray does not intersect with the cylinder
//	if (disc < EPSILON)
//		return false;
//	return true;
//}
