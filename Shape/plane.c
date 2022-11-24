#include "../Include/miniRT.h"

/*
 ?  for the plane configuration :
 * ∗ x,y,z coordinates: 0.0, 0.0, -10.0
 *		∗ 3d normalized orientation vector. In range [-1,1] for each x,y,z axis:
 *		0.0, 0.0, 1.0
 *		∗ R,G,B colors in range [0-255]: 0, 0, 255
 */

bool	intersectPlane(t_minirt *rt, t_ray ray, float *t, int *color)
{
	int	i;
	float tmin;
	float hd;
	t_Plane *tPlane;
	t_intersect closestPlane;

	i = -1;
	hd = EPSILON;
	tPlane = rt->Plane;
	closestPlane.tmin = FLT_MAX;
	while (++i < rt->Data->shape.pl)
	{
		float p = v_dot(tPlane[i].ray.direction, ray.direction);
		t_point resultOfSub = v_sub(tPlane[i].ray.origin, ray.origin);
		tmin = v_dot(resultOfSub, tPlane[i].ray.direction) / p;

		if (tmin > EPSILON)
		{
			// true tmin = 1.0  true 0.5
			if (closestPlane.tmin > tmin) {
				closestPlane.closestPoint = tPlane[i].ray.origin;
				closestPlane.color = tPlane[i].color;
				closestPlane.tmin = tmin;
			}
		}
	}
	if (closestPlane.tmin == FLT_MAX)
	{
		*t = FLT_MAX;
		return false;
	}
    *t = closestPlane.tmin;
	*color = rgb(closestPlane.color);
	return true;
}

// bool	intersectPlane(t_minirt *rt, t_ray ray, float *t, int *color)
// {
// 	float tmin;
// 	float hd;
// 	t_Plane *tPlane;
// 	t_Plane *closestPlane;

// 	hd = EPSILON;
// 	tPlane = rt->Plane;
// 	closestPlane = NULL;
// 	while (tPlane)
// 	{
// 		float p = v_dot(tPlane->normal, ray.direction);
// 		t_point resultOfSub = v_sub(tPlane->plane_point, ray.origin);
// 		tmin = v_dot(resultOfSub, tPlane->normal) / p;
// 		if (tmin > EPSILON)
// 		{
// 			closestPlane = tPlane;
// 			hd = tmin;
// 		}
// 		tPlane = tPlane->next;
// 	}
// 	if (!closestPlane)
// 	{
// 		*t = FLT_MAX;
// 		return false;
// 	}
// 	*t = hd;
// 	rt->Plane->normal = closestPlane->normal;
// 	rt->Plane->local_hit_point = v_adding(ray.origin, v_mul(hd, ray.direction));
// 	*color = rgb(closestPlane->color);
// /*	if (*t > EPSILON)
// 	{
// 		rt->Plane->normal = rt->Plane->normal;
// 		rt->Plane->local_hit_point = v_adding(ray.origin, v_mul(*t, ray.direction));
// 		return true;
// 	}*/
// 	return true;
// }