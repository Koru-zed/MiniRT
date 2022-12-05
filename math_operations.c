#include "Include/miniRT.h"

double	v_dot(const t_point u, const t_point v)
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

t_point v_mul(const double t,  t_point p)
{
	t_point a;

	a.x = p.x * t;
	a.y = p.y * t;
	a.z = p.z * t;
	return a;
}

t_point v_division(t_point p, double t)
{
	return v_mul(1/t, p);
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

int rgb(const t_color rgb)
{
	int color;

	color =  ((rgb.r << 16) + (rgb.g << 8) + rgb.b);
	return (color);
}



double 	length(t_point p)
{
	return (p.x * p.x + p.y * p.y + p.z * p.z);
}

// magnitude
double length_squared(t_point p)
{
	return (sqrt(length(p)));
}

/*
 ! " P(t) = A + tb ", Here P is a 3D position along a line in 3D,
 ! A is the ray origin and b is the ray direction
*/
t_point	at(double t, t_ray *r) {
	t_point	m;

	m = v_mul(t, r->direction);
	return v_adding(r->origin, m);
}

/*
 * With that, you can turn any vector
 * (or rather, any vector with a nonzero magnitude) into a unit vector
 */
t_point	normalizing(t_point p)
{
	double	mag;

	mag = length_squared(p);
	if (mag > 0) {
		p.x /= mag;
		p.y /= mag;
		p.z /= mag;
	}
	return (p);
}

t_point	unit_vector(t_point v)
{
	return v_mul(length_squared(v),v);
}

t_matrix	cross_matrix(t_matrix M1, t_matrix M2)
{
	int			i;
	int         j;
	t_matrix	M12;

	i = 0;
	while (i < 4)
	{
		j = 0;
        while (j < 4)
		{
			M12.M[i][j] = M1.M[i][0] * M2.M[0][j] + \
						  M1.M[i][1] * M2.M[1][j] + \
						  M1.M[i][2] * M2.M[2][j] + \
						  M1.M[i][3] * M2.M[3][j];
			j++;
		}
		i++;
	}
	return (M12);
}

// t_matrix	cross_matrix(t_matrix src, t_matrix mult)
// {
// 	t_matrix	res;
// 	int				i;
// 	int				j;

// 	i = 0;
// 	while (i < 4)
// 	{
// 		j = 0;
// 		while (j < 4)
// 		{
// 			res.M[i][j] = src.M[i][0] * mult.M[0][j] + \
// 			src.M[i][1] * mult.M[1][j] \
// 			+ src.M[i][2] * mult.M[2][j] + src.M[i][3] * mult.M[3][j];
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (res);
// }

t_point	mul_point_matrix(t_point p, t_matrix m)
{
	t_point	Point;

	Point.x = p.x * m.M[0][0] + p.y * m.M[1][0] + p.z * m.M[2][0] + m.M[3][0];
	Point.y = p.x * m.M[0][1] + p.y * m.M[1][1] + p.z * m.M[2][1] + m.M[3][1];
	Point.z = p.x * m.M[0][2] + p.y * m.M[1][2] + p.z * m.M[2][2] + m.M[3][2];
	return (Point);
}
