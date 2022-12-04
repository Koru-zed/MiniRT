
#include "../Include/miniRT.h"




t_point new_point(double x, double y, double z)
{
	t_point pos;

	pos.x = x;
	pos.y = y;
	pos.z = z;
	return pos;
}
t_color add_color(const size_t *c)
{
	t_color obj;

	obj.r = (int)c[0];
	obj.g = (int)c[1];
	obj.b = (int)c[2];
	return obj;
}

double	get_root(double sqrt_disc, double b, double a)
{
	double	t1;
	double	t2;
	double	t;
	double	min;
	double	max;

	t1 = (-b + sqrt_disc) / (2 * a);
	t2 = (-b - sqrt_disc) / (2 * a);
	min = fmin(t1, t2);
	max = fmax(t1, t2);
	if (min >= EPSILON)
		t = min;
	else
		t = max;
	return (t);
}

bool 	intersectRaySphere(t_ray r, t_minirt *rt, double *t,t_hit *pHit)
{

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
	 r.direction = normalizing(r.direction);
	hitDestance = FLT_MAX;
	closestSphere = NULL;
	A = v_dot(r.direction, r.direction);
	i = -1;
	while (++i < rt->Data->shape.sp) {
		dist = v_sub(r.origin, s[i].center);
		B = 2 * v_dot(r.direction, dist);
		C = v_dot(dist, dist) - (s[i].radius * s[i].radius);
		discriminant = pow(B, 2) - (4 * A * C);
		if (discriminant < EPSILON)
			continue ;
		// printf("Sepher\n");
		sqrt_discr = sqrt(discriminant);
		t_min = get_root(sqrt_discr, B, A);
		if (t_min < hitDestance)
		{
			hitDestance = t_min;
			closestSphere = &s[i];
			if (rt->Mlx->mouse)
				rt->Mlx->obj.index = i;
		}
	}
	if (!closestSphere)
		return false;
	*t = hitDestance;
	(pHit)->hit_pos = v_adding(r.origin, v_mul(hitDestance, r.direction));
	(pHit)->obj_color = add_color(closestSphere->color);
	(pHit)->normal = normalizing(v_sub((pHit)->hit_pos, closestSphere->center));
//	(*pHit)->normal = normalizing((*pHit)->hit_pos);
	return true;
}
	/* We need a vector representing the distance between the start of
	 * the ray and the position of the circle.
	 * This is the term (p0 - c)
	 */
//	*color = rgb(closestSphere->color);
