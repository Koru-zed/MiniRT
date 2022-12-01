
#include "../Include/miniRT.h"




t_point new_point(double x, double y, double z)
{
	t_point pos;

	pos.x = x;
	pos.y = y;
	pos.z = z;
	return pos;
}

bool intersectRaySphere(t_ray r, t_minirt *rt, double *t, int *color){

	double t_min;
	t_point dist;
	double discriminant;
	double C;
	double B;
	double sqrt_discr;
	double A;
	t_Sphere *closestSphere;
	t_Sphere *s;
	double hitDestance;
	int i;
	s = rt->Sphere;
	hitDestance = FLT_MAX;
	closestSphere = NULL;
	A = v_dot(r.direction, r.direction);
	*t = FLT_MAX;
	i = -1;
	while (++i < rt->Data->shape.sp) {
		dist = v_sub(r.origin, s[i].center);
		B = 2 * v_dot(r.direction, dist);
		C = v_dot(dist, dist) - (s[i].radius * s[i].radius);
		discriminant = B * B - 4.0f * A * C;
		sqrt_discr = sqrtf(discriminant);
		t_min = (-B - sqrt_discr) / (2.0f * A);
		if (t_min < hitDestance)
		{
			hitDestance = t_min;
			closestSphere = &s[i];
			if (rt->Mlx->mouse)
				rt->Mlx->obj.index = i;
		}
	}
	if (0 >= closestSphere)
	{
		*color = BLACK;
		return false;
	}
	*t = hitDestance;
	*color = rgb(closestSphere->color);
	return true;
}