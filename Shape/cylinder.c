#include "../Include/miniRT.h"

/*
 *  ∗ identifier: cy
	* cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255
	* ∗ x,y,z coordinates: 50.0,0.0,20.6
	* ∗ 3d normalized orientation vector. In range [-1,1] for each x,y,z axis: 0.0,0.0,1.0
	* ∗ the cylinder diameter: 14.2
	* ∗ the cylinder height: 21.42
	* ∗ R,G,B colors in range [0,255]: 10, 0, 255
 */
//bool	cylinder_intersection(t_minirt *rt, t_ray *ray)
//{
//	double r = rt->Cylinder->diameter / 2;
//	double a = powf(ray.dir.x, 2.0) + powf(ray.dir.z, 2.0);
//	double b = 2.0 * ray.origin.x * ray.dir.x + 2.0 * ray.origin.z * ray.dir.z;
//	double c = powf(ray.origin.x, 2.0) + powf(ray.origin.z, 2) - r; // they put 1 i don't know why
//	double disc = powf(b, 2) - 4 * a * c;
//	// ? if the disc is equals to 0  the ray does not intersect with the cylinder
//	if (disc < EPSILON)
//		return false;
//	return true;
//}

double	calc_root(double top_roco, double toprd, double h_2, double t)
{
	double	root;

	if (t < 0)
		root = -top_roco / toprd;
	else
		root = (h_2 - top_roco) / toprd;
	return (root);
}

double	vec_dot(t_point u, t_point v)
{
	double	distance;

	distance = (u.x * v.x) + (u.y * v.y) + (u.z * v.z);
	return (distance);
}


void print_point(t_point p)
{
	printf("p.x = [%f] | ", p.x);
	printf("p.y = [%f] | ", p.y);
	printf("p.z = [%f]\n", p.z);
	printf("************************************************\n");

}

double	get_root(double disc, double b, double a)
{
	double	t1;
	double	t2;
	double	t;
	double	min;
	double	max;

	t1 = (-b + sqrt(disc)) / (2 * a);
	t2 = (-b - sqrt(disc)) / (2 * a);
	min = fmin(t1, t2);
	max = fmax(t1, t2);
	if (min >= EPSILON)
		t = min;
	else
		t = max;
	return (t);
}
t_color convet(int *c)
{
	t_color re;

	re.r = c[0];
	re.g = c[1];
	re.b = c[2];
	return re;
}
bool	cylinder_intersection(t_minirt *rt, t_ray ray, double *t, t_hit *hit)
{
	int i = -1;
	double t_min;

	*t = FLT_MAX;
	t_min = FLT_MAX;
	t_Cylinder *cy=  rt->Cylinder;
	ray.direction = normalizing(ray.direction);
	while (++i < rt->Data->shape.cy)
	{
		// t_point A = v_mul(cy[i].height, cy[i].orientation); //to find orign of top
		// t_point B = normalizing(A); //to find direction of top
		// t_point top = v_mul(cy[i].height, B); //find top point
		// double h_2 = cy[i].height * cy[i].height;
		// t_point ro = v_sub(ray.origin, cy[i].cordinates);
		// double a = h_2 - v_dot(top, ray.direction) * v_dot(top, ray.direction);
		// double b = h_2 * v_dot(ro, ray.direction) - v_dot(top, ro) * v_dot(top, ray.direction);
		// double c = h_2 * v_dot(ro, ro) - v_dot(top, ro)
		// 								* v_dot(top, ro) - (cy[i].redius) * (cy[i].redius) * h_2;

		t_point A = v_mul(cy[i].height, cy[i].orientation); //to find orign of top
		t_point B = normalizing(A); //to find direction of top
		t_point top = v_mul(cy[i].height, B); //find top point
		// Clear
		// printf(top);
		t_point X = v_sub(ray.origin, top);
		t_point hHat = normalizing(v_sub(top, v_adding(top, v_mul(cy[i].height, cy[i].orientation))));

		double a = v_dot(ray.direction, ray.direction) - pow(v_dot(ray.direction, hHat), 2);
		double b = 2 * (v_dot(ray.direction, X) - (v_dot(ray.direction, hHat) * v_dot(X, hHat)));
		double c = v_dot(X, X) - pow(v_dot(X, hHat), 2) - pow(cy[i].redius, 2);
		double discriminant = pow(b, 2) - (4 * a * c);
		if (discriminant < EPSILON)
			continue ;
//		t_min = get_root(discriminant, b, a);
		double	t1;
		double	t2;
		double	min;
		double	max;

		t1 = (-b + sqrt(discriminant)) / (2 * a);
		t2 = (-b - sqrt(discriminant)) / (2 * a);
		min = fmin(t1, t2);
		max = fmax(t1, t2);
		double m = (v_dot(ray.direction, v_mul(min, hHat))) + v_dot(X, hHat);
		double m1 = (v_dot(ray.direction, v_mul(max, hHat))) + v_dot(X, hHat);
		if (m > EPSILON && m <= cy[i].height)
		{
			if (min < *t)
			{
				*t= min;
				hit->obj_color = convet((int *)cy[i].color);
				if (rt->Mlx->mouse)
					rt->Mlx->obj.index = i;
			}
		}
		else if (m1 > EPSILON && m1 <= cy[i].height)
		{
			if (max < *t)
			{
				*t= max;
				hit->obj_color = convet((int *)cy[i].color);
				if (rt->Mlx->mouse)
					rt->Mlx->obj.index = i;
			}
		}
	}
	if (*t == FLT_MAX)
		return false;
	return true;
}
