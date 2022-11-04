#include "Include/miniRT.h"

//bool	intersectRaySphere(t_ray *r, t_sphere *s, float *t)
//{
//	bool	retval;
//	float	A;
//	t_point	dist;
//
//	retval = false;
//	A = dot(r->dir, r->dir);
//	dist = sub(r->start, s->pos);
//	float B = 2 * dot(dist, dist);
//	float C = dot(dist, dist) - (s->radius * s->radius);
//	/* * Solving the discriminant */
//	float discr = B * B - 4 * A * C;
//	/* * If the discriminant is negative, there are no real roots.
//	  * Return false in that case as the ray misses the sphere.
//	  * Return true in all other cases (can be one or two intersections)
//	  *  t, the solution to the equation represents the closest point
//	  *  where our ray intersect with the sphere
//	  */
//	if (discr < 0)
//		retval = false;
//	else if (!disc)
//		t =
//	else
//	{
//		float sqrt_discr = sqrtf(discr);
//		float t0 = (-B + sqrt_discr) / 2;
//		float t1 = (-B - sqrt_discr) / 2;
//		//  * we want the closest one
//		if (t0 > t1)
//			t0 = t1;
//		/*  * Verify t0 larger than 0 and less than the original t */
//		if ((t0 > 0.0001f) && (t0 < *t)){
//			*t = t0;
//			retval = true;
//		}
//		else
//			retval = false;
//	}
//	return retval;
//}|

t_point	to_point(float x, float y, float z)
{
	t_point pos;

	pos.x = x;
	pos.y = y;
	pos.z = z;
	return pos;
}

//bool intersectRaySphere(t_ray *r, t_Sphere *s)
//{
//	bool	retval;
//	float	A;
//	t_point	dist;
//	t_point	pos;
//
//	pos = convert_to_point(s);
//	retval = false;
//	A = dot(r->dir, r->dir);
//	dist = sub(r->start, pos);
//	float B = 2 * dot(r->dir, dist);
//	float C = dot(dist, dist) - (s->radius * s->radius);
//	/* * Solving the discriminant */
//	float discr = B * B - 4 * A * C;
//	/* * If the discriminant is negative, there are no real roots.
//	  * Return fal†se in that case as the ray misses the sphere.
//	  * Return true in all other cases (can be one or two intersections)
//	  *  t, the solution to the equation represents the closest point
//	  *  where our ray intersect with the sphere
//	  */
//	if (discr < 0)
//		retval = false;
//	else
//		retval = true;
//	return retval;
//}
bool intersectRaySphere(t_ray *r, t_Sphere *s, float *t){

	/* A = d.d, the vector dot product of the direction */
	float A = dot(r->direction, r->direction);

	/* We need a vector representing the distance between the start of
	 * the ray and the position of the circle.
	 * This is the term (p0 - c)
	 */
	t_point dist = sub(r->origin, s->cordinates);

	/* 2d.(p0 - c) */
	float B = 2 * dot(r->direction, dist);

	/* (p0 - c).(p0 - c) - r^2 */
	float C = dot(dist, dist) - (s->radius * s->radius);

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