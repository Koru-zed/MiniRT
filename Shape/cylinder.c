#include "../Include/miniRT.h"

bool	check_caps(t_ray ray, double t, double r)
{
	double x = ray.origin.x + t * ray.direction.x;
	double z = ray.origin.z + t * ray.direction.z;
	return (powf(x, 2) + powf(z, 2) <= powf(r, 2.0f));
}

t_point local_normal_at(t_Cylinder *cy, t_point p)
{
	// compute the square of the distance from the y axis
	double dist = powf(p.x, 2) + powf(p.z, 2);
	if (dist < 1 && p.y >= cy->cyMax - EPSILON)
		return new_point(0, 1, 0);
	else if (dist < 1 && p.y <= cy->cyMin + EPSILON)
	return new_point(0, -1, 0);
	return new_point(p.x, 0, p.y);
}

void	ft_swap(double *a, double *b);


void	find_t(t_minirt *rt, t_ray ray, double *t)
{
	t_Cylinder *cy;
	double A;
	double B;
	double C;
	double discriminant;


	cy = rt->Cylinder;
	t_point dir_n = normalizing(ray.direction);
	A = powf(dir_n.x, 2.0) + powf(dir_n.z, 2);
	if (A < EPSILON)
		return ;
	B = 2.0f * ray.origin.x * dir_n.x + 2 * ray.origin.z * dir_n.z;
	C = powf(ray.origin.x, 2.0f) + powf(ray.origin.z, 2.0) - powf(cy->redius, 2.0); // 1. for raduis
	discriminant = powf(B, 2.0f) - 4.0f * A * C;
	if (discriminant < EPSILON)
	{
		t[0] = INFINITY;
		t[1] = INFINITY;
		return;
	}
	t[0] = (-B - sqrtf(discriminant)) / (2 * A);
	t[1] = (-B + sqrtf(discriminant)) / (2 * A);
	if (t[0] > t[1])
		ft_swap(&t[0], &t[1]);
}
void	ft_swap(double *a, double *b)
{
	double tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}
bool intersect_caps(t_Cylinder cy, t_ray ray)
{
	if (ray.direction.y < EPSILON)
		return false;

//	# check for an intersection with the lower end cap by intersecting
//	# the ray with the plane at y=cyl.minimum
	double t = (cy.cyMin - ray.origin.y) / ray.direction.y;
	if (check_caps(ray, t, cy.redius))
		return true;
	t = (cy.cyMax - ray.origin.y) / ray.direction.y;
	if (check_caps(ray, t, cy.redius))
		return true;
	return false;
}


bool	cylinder_int(t_minirt *rt, t_ray ray)
{
	t_Cylinder *cy;
	double t[2];

	rt->Cylinder->cyMin = 0;
	rt->Cylinder->cyMax = rt->Cylinder->height;
	cy = rt->Cylinder;
	ray.direction = normalizing(ray.direction);
	find_t(rt, ray, t); // above this
	if (t[0] != INFINITY && t[1] != INFINITY) {
		ray.direction = normalizing(ray.direction);
		double y0 = ray.origin.y + t[0] * ray.direction.y;
//		if (y0 >= cy->cordinates.y && y0 <= cy->cordinates.y + cy->height)
//			return true;
		 if (cy->cyMin < y0 && y0 < cy->cyMax) {
			 // t[0] well be returned for calculating the position
			 return true;
		 }
		double y1 = ray.origin.y + t[1] * ray.direction.y;
//		if (y1 >= cy->cordinates.y && y1 <= cy->cordinates.y + cy->height)
//			return true;
		 if (cy->cyMin < y1 && y1 < cy->cyMax) {
			 // t[1] well be returned for calculating the position
			 return true;
		 }
	}
//	 return intersect_caps(*cy, ray) this function only checks for end caps to be closed
//	return  false;
}