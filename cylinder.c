 #include "Include/miniRT.h"

 /*
  *  ∗ identifier: cy
 	* cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255
 	* ∗ x,y,z coordinates: 50.0,0.0,20.6
 	* ∗ 3d normalized orientation vector. In range [-1,1] for each x,y,z axis: 0.0,0.0,1.0
 	* ∗ the cylinder diameter: 14.2
 	* ∗ the cylinder height: 21.42
 	* ∗ R,G,B colors in range [0,255]: 10, 0, 255
  */
 /*
  * ** x(t) = d0t + p0
  * ** y(t) = d1t + p1
  * ** z(t) = d2t + p2
  */

 void	ft_swap(float *a, float *b);

 bool	cylinder_int(t_minirt *rt, t_ray *ray, const int fd)
 {
	 (void )fd;
	 t_Cylinder *cy;
	 float A;
	 float B;
	 float C;
//	bool t1Valid, t2Valid, t3Valid, t4Valid;
	 float delta;

	 cy = rt->Cylinder;
	 A = powf(ray->direction.x, 2.0) + powf(ray->direction.z, 2);
	 B = 2.0f * ray->origin.x * (powf(ray->origin.x - cy->cordinates.x, 2.0) +  ray->direction.z * (powf(ray->origin.z - cy->cordinates.z, 2.0)));
//	 C = powf(ray->origin.x, 2.0f) + powf(ray->origin.y, 2.0) - powf(cy->radius, 2.0); // 1. for raduis
	C = powf(ray->origin.x - cy->cordinates.x, 2.0) + powf(ray->origin.z - cy->cordinates.z, 2.0) - powf(cy->radius, 2.0);
	 delta = powf(B, 2.) - 4.0f * A * C;
	 if (fabs(delta) < EPSILON)
		 return false;
	 float t1 = -B - sqrtf(delta) / (2.0 * C);
	 float t2 = -B + sqrtf(delta) / (2.0 * C);
	 float t;
	 if (t1 > t2)
		 t = t1;
	 else
		 t = t2;
	 float r = ray->origin.y + t * ray->direction.y;
	 if (r >= cy->cordinates.y && r <= cy->cordinates.y + cy->height)
		 return true;
	 return false;
 }

 void	ft_print_vector(const t_point p, int fd)
 {
 	dprintf(fd, "p.x = {%f}\t|", p.x);
 	dprintf(fd, "p.y = {%f}\t|", p.y);
 	dprintf(fd, "p.z = {%f}|\n", p.z);
 }

 void	ft_swap(float *a, float *b)
 {
 	float tmp;

 	tmp = *a;
 	*a = *b;
 	*b = tmp;
 }
//x ← ray.origin.x + t * ray.direction.x z ← ray.origin.z + t * ray.direction.z
// bool check_caps(t_ray ray, float t)
// {
//	 float x = ray.origin.x + t * ray.direction.x;
//	 float z = ray.origin.z + t * ray.direction.z;
//	 return (powf(x, 2) + powf(z, 2) <= 1.);
// }
//
//bool	find_t(t_minirt *rt, t_ray *ray, float *t) {
//	t_Cylinder *cy;
//	float A;
//	float B;
//	float C;
////	bool t1Valid, t2Valid, t3Valid, t4Valid;
//	float discriminant;
//
//	cy = rt->Cylinder;
//	A = powf(ray->direction.x, 2.0) + powf(ray->direction.y, 2);
//	B = 2.0f * ray->origin.x * ray->direction.x + 2 * ray->origin.y * ray->direction.y;
//	C = powf(ray->origin.x, 2.0f) + powf(ray->origin.y, 2.0) - powf(cy->radius, 2.0); // 1. for raduis
//	discriminant = sqrtf(powf(B, 2.) - 4.0f * A * C);
//	if (discriminant > EPSILON) {
//		t[0] = (-B + discriminant) / (2 * A);
//		t[1] = (-B - discriminant) / (2 * A);
//		if (t[0] < EPSILON)
//		{
//			t[0] = INFINITY;
//			t[1] = INFINITY;
//			return false;
//		}
//		return true;
//		// compute the point intersection.
////		t_point p1 = v_adding(ray->origin, v_mul(t[0], ray->direction));
////		t_point p2 = v_adding(ray->origin, v_mul(t[1], ray->direction));
//	}
//	t[0] = INFINITY;
//	t[1] = INFINITY;
//	return false;
//}
////	float y0 = ray->origin.y + t_mi n * ray->direction.y;
// bool	cylinder_intersection(t_minirt *rt, t_ray *ray, const int fd)
// {
// 	(void)fd;
//	 float	t[2];
//	 t_Cylinder	*cy;
//
//	 cy = rt->Cylinder;
//	 float minimum = INFINITY;
//	 float maximum = INFINITY;
//	if (find_t(rt, ray, t))
//	{
//		if (t[0] < t[1])
//			ft_swap(&t[0], &t[1]);
//		t_point line = v_adding(ray->origin, v_mul(t[0], ray->direction));
//		return true
//
//	}
// 	return false;
// }