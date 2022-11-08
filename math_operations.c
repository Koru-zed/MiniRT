#include "Include/miniRT.h"

float	v_dot(const t_point u, const t_point v)
{
	return (u.x * v.x
			+ u.y * v.y
			+ u.z * v.z);
}

t_point	v_cross(const t_point u, const t_point v) {
	
	t_point vec;

	vec.x = u.y * v.z - u.z * v.y;
	vec.y = u.z * v.x - u.x * v.z;
	vec.z = u.x * v.y - u.y * v.x;
	return vec;
}

t_point v_mul(const float t,  t_point p)
{
	t_point a;

	a.x = p.x * t;
	a.y = p.y * t;
	a.z = p.z * t;
	return a;
}

t_point v_division(t_point p, float t)
{
	return mul(1/t, p);
}

t_point	v_adding(t_point p, t_point v)
{
	t_point a;
	a.x = p.x + v.x;
	a.y = p.y + v.y;
	a.z = p.z + v.z;
	return a;
}

t_point v_sub(t_point center, t_point origin)
{
	t_point p;

	p.x = center.x - origin.x;
	p.y = center.y - origin.y;
	p.z = center.z - origin.z;
	return (p);
}

unsigned long createRGB(double r, double g, double b)
{
	int ir = (int)(255.999 * r);
	int ig = (int)(255.999 * g);
	int ib = (int)(255.999 * b);
	
	int i = (ir << 16) +(ig  <<  8) + ib ;
	// printf("co{%d}", i);
	return (i);
}


float 	length_squared(t_point p)
{
	return (p.x * p.x + p.y * p.y + p.z * p.z);
}

// magnitude
float length(t_point p)
{
	return sqrtf (length_squared(p));
}

/*
 * With that, you can turn any vector
 * (or rather, any vector with a nonzero magnitude) into a unit vector
 */
t_point	normalizing(t_point p)///unit_vector
{
	t_point a;
	float	mag;

	mag = length(p);
	a.x = p.x / mag;
	a.y = p.y / mag;
	a.z = p.z / mag;
	return (a);
}

t_point	unit_vector(t_point v)
{
	return mul(length_squared(v),v);
}