
#include "Include/miniRT.h"




t_point new_point(float x, float y, float z)
{
	t_point pos;

	pos.x = x;
	pos.y = y;
	pos.z = z;
	return pos;
}

bool intersectRaySphere(t_ray r, t_minirt *rt, float *t, int *color){

	float t_min;
	t_point dist;
	float discriminant;
	float C;
	float B;
	float sqrt_discr;
	float A;
	t_Sphere *closestSphere;
	t_Sphere *s;
	float hitDestance;

	s = rt->Sphere;
	/* A = d.d, the vector dot product of the direction */
	hitDestance = FLT_MAX;
	closestSphere = NULL;
	A = v_dot(r.direction, r.direction);
	*t = FLT_MAX;
	while (s) {
		dist = v_sub(s->center, r.origin);

		/* 2d.(p0 - c) */
		B = 2 * v_dot(r.direction, dist);

		/* (p0 - c).(p0 - c) - r^2 */
		C = v_dot(dist, dist) - (s->radius * s->radius);

		/* Solving the discriminant  quadratic equation*/
		discriminant = B * B - 4.0f * A * C;

		/* If the discriminant is negative, there are no real roots.
		 * Return false in that case as the ray misses the sphere.
		 * Return true in all other cases (can be one or two intersections)
		 */
//		if (discriminant < 0.0f)
//			continue;
		sqrt_discr = sqrtf(discriminant);
		t_min = (-B - sqrt_discr) / (2.0f * A);
		if (t_min < hitDestance)
		{
			hitDestance = t_min;
			closestSphere = s;
		}
		s = s->next;
	}
	if (!closestSphere)
	{
		*color = BLACK;
		return false;
	}
	*t = hitDestance;
//	t_point origin = v_sub(r->origin, closestSphere->center);
//	t_point hitPoint = v_adding(origin, v_mul(hitDestance, r->direction));

//	else
//	{
//		sqrt_discr = sqrtf(discriminant);
//		t_min = (-B - sqrt_discr) / (2.0f * A);
//		if (t_min > EPSILON)
//		{
//			*t = t_min;
//			// todo : compute the local hit point and normal
//			return true;
//		}
//		t_min = (-B + sqrt_discr) / (2.0f * A);
//		if (t_min > EPSILON)
//		{
//			*t = t_min;
//			// todo : compute the local hit point and normal
//			return true;
//		}
//	}

	/* We need a vector representing the distance between the start of
	 * the ray and the position of the circle.
	 * This is the term (p0 - c)
	 */
	*color = rgb(closestSphere->color);
	return true;
}