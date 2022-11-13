#include "Include/miniRT.h"

t_point	convert_to_point(float *s)
{
	t_point pos;

	pos.x = s[0];
	pos.y = s[1];
	pos.z = s[2];
	return pos;
}
//
float	intersect(t_ray *r, t_Sphere *s)
{
	t_point	oc;
	t_point	origin;

	origin = convert_to_point(s->cordinates);
	oc = sub(r->origin, origin);
	float a = length_squared(r->dir);
	float half_b = dot(oc, r->dir);
	float c = length_squared(oc) - s->radius * s->radius;
	float discriminant = half_b * half_b -  a * c;
	if (discriminant < 0.0f)
	{
		printf("true\n");
		return -1.0f;
	}
	return (-half_b - sqrtf(discriminant)) / a;
}
t_point new_point(float x, float y, float z)
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
//	pos = convert_new_point(s);
//	retval = false;
//	A = dot(r->dir, r->dir);
//	dist = sub(r->start, pos);
//	pos = convert_to_point(s);
//	retval = false;
//	A = dot(r->dir, r->dir);
//	dist = sub(r->origin, pos);
//	float B = 2 * dot(r->dir, dist);
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
//	else
//		retval = true;
//	return retval;
//}
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
<<<<<<< HEAD
		*color = 0xFF0000;
//		float sqrt_discr = sqrtf(discriminant);
//		float t0 = (-B - sqrt_discr) / (2.0f * A);
//		float t1 = (-B + sqrt_discr) / (2.0f * A);
		// hit point
//		float x = r->start.x + r->dir.x * t0;
//		float y = r->start.y + r->dir.y * t0;
//		float z = r->start.z + r->dir.z * t0;
//		*color = createRGB(x, y, z);
//		float x1 = r->start.x + r->dir.x * t1;
//		float y1 = r->start.y + r->dir.y * t1;
//		float z1 = r->start.z + r->dir.z * t1;
=======
		printf("hi\n");
		float sqrt_discr = sqrtf(discriminant);
		*t = (-B - sqrt_discr) / (2.0f * A);
//		float t0 = (-B + sqrt_discr) / (2.0f * A);
>>>>>>> 6cd3fbdb64b2a75113e16f421a721ae02af7e8e1
		return true;
	}
}