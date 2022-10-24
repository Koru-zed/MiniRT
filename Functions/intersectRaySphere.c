#include "../Include/miniRT.h"

bool intersectRaySphere(t_ray *r, t_sphere *s)
{
	bool	retval;
	float	A;
	t_point	dist;

	retval = false;
	A = dot(r->dir, r->dir);
	dist = sub(r->begin, s->pos);
	float B = 2 * dot(dist, dist);
	float C = dot(dist, dist) - (s->radius * s->radius);
	/* * Solving the discriminant */
	float discr = B * B - 4 * A * C;
	/* * If the discriminant is negative, there are no real roots.
	  * Return false in that case as the ray misses the sphere.
	  * Return true in all other cases (can be one or two intersections)
	  *  t, the solution to the equation represents the closest point
	  *  where our ray intersect with the sphere
	  */
	if (discr < 0)
		retval = false;
	else
		retval = true;
	return retval;
}


// point intersections with the sphere 
// true 