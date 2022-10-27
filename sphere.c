#include "Include/miniRT.h"

bool	float_equal(float a, float b)
{
	if (fabsf(a - b) < EPSILON)
		return true;
	return false;
}

t_matrix	*creat_matrix(int r, int c, t_point p)
{
	t_matrix	*matrix;

	matrix = ft_calloc(1, sizeof(t_matrix));
	if (!matrix)
		return (void *)0;
	matrix->mat = ft_calloc(4, sizeof(float *));

}
// Matrix multiplication computes the dot product of every row-column combination in the two matrices
t_matrix *matrix_multiplication(t_matrix *a, t_matrix *b)
{
	t_matrix *m;
	int 	r;
	int 	c;

	r = -1;
	c = -1;
	m = ft_calloc(1, sizeof(t_matrix));
	m->mat = ft_calloc(4, sizeof(float*));
	while (r++ < 3)
	{
		m->mat[r] = ft_calloc(4, sizeof(float ));
		while (c++ < 3)
		{
			m->mat[r][c] = a->mat[r][0] * b->mat[0][c] + a->mat[r][1] * b->mat[1][c]
					+ a->mat[r][2] * b->mat[2][c] + a->mat[r][3] * b->mat[3][c];
		}
	}
	return m;
}

t_point	convert_to_point(t_Sphere *s)
{
	t_point pos;

	pos.x = s->cordinates[0];
	pos.y = s->cordinates[1];
	pos.z = s->cordinates[2];
	return pos;
}
//
//float	intersectRaySphere(t_ray *r, t_Sphere *s)
//{
//	t_point	oc;
//	t_point	origin;
//
//	origin = convert_to_point(s);
//	oc = sub(r->start, origin);
//	float a = dot(r->dir, r->dir);
//	float b = 2.0f * dot(oc, r->dir);
//	float c = dot(oc, oc) - s->radius * s->radius;
//	float discriminant = b*b - 4*a*c;
//	if (discriminant < 0.0f)
//		return -1.0f;
//	return (-b - sqrtf(discriminant)) / (2.0f*a);
//}

bool intersectRaySphere(t_ray *r, t_Sphere *s)
{
	bool	retval;
	float	A;
	t_point	dist;
	t_point	pos;

	pos = convert_to_point(s);
	retval = false;
	A = dot(r->dir, r->dir);
	dist = sub(r->start, pos);
	float B = 2 * dot(r->dir, dist);
	float C = dot(dist, dist) - (s->radius * s->radius);
	/* * Solving the discriminant */
	float discr = B * B - 4 * A * C;
	/* * If the discriminant is negative, there are no real roots.
	  * Return fal†se in that case as the ray misses the sphere.
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
//bool intersectRaySphere(t_ray *r, t_Sphere *s, float *t){
//
//	/* A = d.d, the vector dot product of the direction */
//	float A = dot(r->dir, r->dir);
//
//	/* We need a vector representing the distance between the start of
//	 * the ray and the position of the circle.
//	 * This is the term (p0 - c)
//	 */
//	t_point	pos;
//
//	pos = convert_to_point(s);
//	t_point dist = sub(r->start, pos);
//
//	/* 2d.(p0 - c) */
//	float B = 2 * dot(r->dir, dist);
//
//	/* (p0 - c).(p0 - c) - r^2 */
//	float C = dot(dist, dist) - (s->radius * s->radius);
//
//	/* Solving the discriminant  quadratic equation*/
//	float discriminant = B * B - 4.0f * A * C;
//
//	/* If the discriminant is negative, there are no real roots.
//	 * Return false in that case as the ray misses the sphere.
//	 * Return true in all other cases (can be one or two intersections)
//	 */
//	if(discriminant < 0.0f)
//		return false;
//	else
//	{
//		float sqrt_discr = sqrtf(discriminant);
//		*t = (-B - sqrt_discr) / (2.0f * A);
////		float t0 = (-B + sqrt_discr) / (2.0f * A);
//		return true;
//	}
//}