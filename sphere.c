#include "Include/miniRT.h"



t_point new_point(float x, float y, float z)
{
	t_point pos;

	pos.x = x;
	pos.y = y;
	pos.z = z;
	return pos;
}

bool intersectRaySphere(t_ray *r, t_Sphere *s, float *t){

	/* A = d.d, the vector dot product of the direction */
	float A = v_dot(r->direction, r->direction);

	/* We need a vector representing the distance between the start of
	 * the ray and the position of the circle.
	 * This is the term (p0 - c)
	 */
	t_point dist = v_sub(r->origin, s->center);

	/* 2d.(p0 - c) */
	float B = 2 * v_dot(r->direction, dist);

	/* (p0 - c).(p0 - c) - r^2 */
	float C = v_dot(dist, dist) - (s->radius * s->radius);

	/* Solving the discriminant  quadratic equation*/
	float discriminant = B * B - 4.0f * A * C;

	/* If the discriminant is negative, there are no real roots.
	 * Return false in that case as the ray misses the sphere.
	 * Return true in all other cases (can be one or two intersections)
	 */
	if(discriminant < 0.0f)
		return false;
	else
	{
		float sqrt_discr = sqrtf(discriminant);
		*t = (-B - sqrt_discr) / (2.0f * A);
//		float t0 = (-B + sqrt_discr) / (2.0f * A);
		return true;
	}
}