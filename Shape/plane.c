#include "../Include/miniRT.h"

/*
 ?  for the plane configuration :
 * ∗ x,y,z coordinates: 0.0, 0.0, -10.0
 *		∗ 3d normalized orientation vector. In range [-1,1] for each x,y,z axis:
 *		0.0, 0.0, 1.0
 *		∗ R,G,B colors in range [0-255]: 0, 0, 255
 */

bool	intersectPlane(t_minirt *rt, t_ray ray, double *t, t_hit **pHit)
{
	int	i;
	double tmin;
	double hd;
	t_Plane *tPlane;
	t_intersect closestPlane;

	i = -1;
	hd = EPSILON;
	tPlane = rt->Plane;
	closestPlane.tmin = FLT_MAX;
	t_point n;
	ray.direction = normalizing(ray.direction);
	while (++i < rt->Data->shape.pl)
	{
		double p = v_dot(tPlane[i].ray.direction, ray.direction);
		t_point resultOfSub = v_sub(tPlane[i].ray.origin, ray.origin);
		tmin = v_dot(resultOfSub, tPlane[i].ray.direction) / p;

		if (tmin > EPSILON)
		{
			// true tmin = 1.0  true 0.5
			if (closestPlane.tmin > tmin) {
				closestPlane.closestPoint = tPlane[i].ray.origin;
				closestPlane.color = tPlane[i].color;
				n = tPlane[i].ray.direction;
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
	(*pHit)->obj_color = add_color(closestPlane.color);
	(*pHit)->hit_pos = v_adding(ray.origin, v_mul(*t, ray.direction));
	(*pHit)->normal = n;
//	*color = rgb(closestPlane.color);
	return true;
}