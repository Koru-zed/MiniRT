
#include "Include/miniRT.h"




t_point new_point(float x, float y, float z)
{
	t_point pos;

	pos.x = x;
	pos.y = y;
	pos.z = z;
	return pos;
}



bool intersectRaySphere(t_ray r, t_minirt *rt, float *t, int *color, t_hit **pHit)
{

	float t_min;
	t_point dist;
	float discriminant;
	float C;
	float B;
	float sqrt_discr;
	float A;
	t_Sphere *closestSphere;
	t_Sphere *s;
	float dis_t;

	s = rt->Sphere;
	/* A = d.d, the vector dot product of the direction */
	dis_t = FLT_MAX;
	closestSphere = NULL;
	r.direction = normalizing(r.direction);
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
		if (t_min < dis_t)
		{
			dis_t = t_min;
			closestSphere = s;
		}
		s = s->next;
	}
	if (!closestSphere)
	{
		*color = BLACK;
		return false;
	}
	*t = dis_t;
//	t_point origin = v_sub(r.origin, closestSphere->center);
	(*pHit)->hit_pos = v_adding(r.origin, v_mul(dis_t, r.direction));
	(*pHit)->normal = normalizing(v_sub((*pHit)->hit_pos, closestSphere->center));

	/* We need a vector representing the distance between the start of
	 * the ray and the position of the circle.
	 * This is the term (p0 - c)
	 */
//	size_t am[3];
//	am[0] = (size_t) ((float )rt->Ambient->color[0] * rt->Ambient->ratio);
//	am[1] = (size_t )((float )rt->Ambient->color[1] * rt->Ambient->ratio);
//	am[2] = (size_t )((float )rt->Ambient->color[2] * rt->Ambient->ratio);
//	size_t res[3];
//
//	res[0] = closestSphere->color[0] * am[0];
//	res[1] = closestSphere->color[1] * am[1];
//	res[2] = closestSphere->color[2] * am[2];
//	*color = rgb(res);
		*color = rgb(closestSphere->color);
	(*pHit)->color[0] = closestSphere->color[0];
	(*pHit)->color[1] = closestSphere->color[1];
	(*pHit)->color[2] = closestSphere->color[2];
	return true;
}