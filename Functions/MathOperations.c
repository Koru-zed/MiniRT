#include "../Include/miniRT.h"

float	dot(const t_point u, const t_point v)
{
	return u.x * v.x
		   + u.y * v.y
		   + u.z * v.z;
}

t_point	cross(const t_point u, const t_point v) {
	t_point vec;
	vec.x = u.y * v.z - u.z * v.y;
	vec.y = u.z * v.x - u.x * v.z;
	vec.z = u.x * v.y - u.y * v.x;
	return vec;
}

t_point mul(const float t,  t_point p)
{
	p.x *= t;
	p.y *= t;
	p.z *= t;
	return p;
}

t_point division(t_point p, float t)
{
	return mul(1/t, p);
}

t_point	adding(t_point p, t_point v)
{
	p.x += v.x;
	p.y += v.y;
	p.z += v.z;
	return p;
}

t_point sub(t_point center, t_point origin)
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
	return (ir << (16 + ig) << (8 + ib));
}

float 	length_squared(t_point p)
{
	return (p.x * p.x + p.y * p.y + p.z * p.z);
}

float length(t_point p)
{
	return sqrtf (length_squared(p));
}

t_point	unit_vector(t_point v)
{
	return mul(length_squared(v),v);
}