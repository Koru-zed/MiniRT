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

// bool	cylinder_intersection(t_minirt *rt, t_ray ray, double *t, int *color)
// {
// 	int i;
// 	t_point p;
// 	t_point	top;
// 	t_point  bottom;
// 	t_Cylinder closestCylinder;
// 	double	_height;
// 	double t1;
// 	double t2;
// 	double t_min;
// 	double t_now;

// 	i = -1;
// 	t_now = FLT_MAX;
// 	while (++i < rt->Data->shape.cy)
// 	{
// 		top = v_mul(rt->Cylinder[i].height, rt->Cylinder[i].orientation);
// 		_height = v_dot(top, top);
// 		bottom = v_sub(ray.origin, rt->Cylinder[i].cordinates);
// 		p.x = _height - (v_dot(top, ray.direction) * v_dot(top, ray.direction));
// 		p.y = (_height * v_dot(top, ray.direction)) - (v_dot(top, bottom) * v_dot(top, ray.direction));
// 		p.z = (_height * v_dot(top, bottom)) - (v_dot(top, bottom) * v_dot(top, bottom)) - (rt->Cylinder[i].redius * rt->Cylinder[i].redius * _height); 
// 		if ((p.y * p.y) - (p.x * p.z) < EPSILON)
// 			continue;
// 		t1 = (-p.y - sqrtf(((p.y * p.y) - (p.x * p.z)))) / p.x;
// 		t2 = v_dot(top, bottom) + (t1 * v_dot(top, ray.direction));
// 		if (t1 > 0 && t1 < _height)
// 			t_min = t2;
// 		else
// 		{
// 			t1 = calc_root(v_dot(top, bottom), v_dot(top, ray.direction), _height, t1);
// 			if (fabs(p.y + (p.x * t1)) < sqrtf((p.y * p.y) - (p.x * p.z)))
// 				t_min = t1;
// 		}
// 		if (t_min < t_now)
// 		{
// 			t_now = t_min;
// 			closestCylinder = rt->Cylinder[i];
// 			if (rt->Mlx->mouse)
// 				rt->Mlx->obj.index = i;
// 		}
// 	}
// 	if (t_min == FLT_MAX)
// 	{
// 		*t = FLT_MAX;
// 		return false;
// 	}
// 	*t = t_min;
// 	*color = rgb(closestCylinder.color);
// 	return true;
// }

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

bool	cylinder_intersection(t_minirt *rt, t_ray ray, double *t, int *color)
{
	int i = -1;
	double t_min;

	*t = FLT_MAX;
	t_min = FLT_MAX;
	t_Cylinder *cy=  rt->Cylinder;
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
		double a = v_dot(ray.direction, ray.direction) - powf(v_dot(ray.direction, cy[i].orientation), 2);
		double b = 2 * (v_dot(ray.direction, X) - (v_dot(ray.direction, cy[i].orientation) * v_dot(X, cy[i].orientation)));
		double c = v_dot(X, X) - powf(v_dot(X, cy[i].orientation), 2) - powf(cy[i].redius, 2);
		double discriminant = powf(b, 2) - (4 * a * c);
		if (discriminant < EPSILON)
			continue ;
		t_min = get_root(discriminant, b, a);
		double m = (v_dot(ray.direction, v_mul(t_min, cy[i].orientation))) + v_dot(X, cy[i].orientation);
		if (m > EPSILON && m <= cy[i].height)
		{
			printf("hello\n");
			t_point p = v_adding(ray.origin, v_mul(t_min, ray.direction));
			t_point q = v_adding(top, v_mul(m, cy[i].orientation));
			double stap1 = v_dot(v_sub(p, q), cy[i].orientation);
			double stap2 = length_squared(v_sub(p, q));
			// double solution = v_dot(v_sub(v_sub(p , top), v_mul(m, cy[i].orientation)), cy[i].orientation);
	// printf ("soution[%f]\n", solution);
 			if (fabs(stap2 - cy[i].redius) < EPSILON)
			{
			// if (t2 > EPSILON && t2 < h_2)
			// 	t_min = t2;
			// t2 = calc_root(v_dot(top, ro), v_dot(top, ray.direction), h_2, t2);
			// if (fabs(b + a * t2) < sqrtf((b * b - a * c)))
			// 	t_min = t1;
				if (t_min < *t)
				{
					*t= t_min;
					*color = rgb(cy[i].color);
					if (rt->Mlx->mouse)
						rt->Mlx->obj.index = i;
				}
			}
		}
	}
	if (*t == FLT_MAX)
		return false;
	else
 		return true;
}

// bool	cylinder_intersection(t_minirt *rt, t_ray ray, double *t, int *color)
// {
// 	*t = FLT_MAX;
//     t_Cylinder *cy=  rt->Cylinder;
//     t_point top = v_mul(cy->height, normalizing(v_mul(cy->height, cy->orientation)));
//     double h_2 = v_dot(top, top);
//     t_point ro = v_sub(ray.origin, cy->cordinates);
//     double a = h_2 - v_dot(top, ray.direction) * v_dot(top, ray.direction);
//     double b = h_2 * v_dot(ro, ray.direction) - v_dot(top, ro) * v_dot(top, ray.direction);
//     double c = h_2 * v_dot(ro, ro) - v_dot(top, ro)
//                                      * v_dot(top, ro) - (cy->redius) * (cy->redius) * h_2;
//     if ((b * b - a * c) < 0)
//         return false;
//     double t1 = (-b - sqrtf((b * b - a * c))) / a;
//     double t2 = v_dot(top, ro) + (t1) * v_dot(top, ray.direction);
//     if (t2 > 0 && t2 < h_2)
// 	{
// 		*t= t1;
//         *color = rgb(cy->color);
//         return true;
// 	}
// 	t2 = calc_root(v_dot(top, ro), v_dot(top, ray.direction), h_2, t2);
//     if (fabs(b + a * t2) < sqrtf((b * b - a * c)))
//     {
// 		*t = t1;
// 		*color = rgb(cy->color);
//         return true;
// 	}
// 	return false;
// }

// static inline double	hit_cylinder(void *cylinder, t_vec3 r_o, t_vec3 rd)
// {
// 	t_cy		*cyl;
// 	t_quadra	p;
// 	t_vec3		top;
// 	t_vec3		roco;
// 	double		h_2;

// 	cyl = (t_cy *)cylinder;
// 	top = vec_multiply(vec_normalize(vec_multiply(cyl->dir, cyl->height)),
// 			cyl->height);
// 	h_2 = vec_dot(top, top);
// 	roco = vec_sub(r_o, cyl->origin);
// 	p.a = h_2 - vec_dot(top, rd) * vec_dot(top, rd);
// 	p.b = h_2 * vec_dot(roco, rd) - vec_dot(top, roco) * vec_dot(top, rd);
// 	p.c = h_2 * vec_dot(roco, roco) - vec_dot(top, roco)
// 		* vec_dot(top, roco) - (cyl->rad) * (cyl->rad) * h_2;
// 	if ((p.b * p.b - p.a * p.c) < 0)
// 		return (-1);
// 	p.t1 = (-p.b - sqrtf((p.b * p.b - p.a * p.c))) / p.a;
// 	p.t = vec_dot(top, roco) + (p.t1) * vec_dot(top, rd);
// 	if (p.t > 0 && p.t < h_2)
// 		return (p.t1);
// 	p.t = calc_root(vec_dot(top, roco), vec_dot(top, rd), h_2, p.t);
// 	if (fabs(p.b + p.a * p.t) < sqrtf((p.b * p.b - p.a * p.c)))
// 		return (p.t);
// 	return (-1);
// }