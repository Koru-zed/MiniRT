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
void	ft_print_vector(const t_point p, int fd)
{
	dprintf(fd, "p.x = {%f}\t|", p.x);
	dprintf(fd, "p.y = {%f}\t|", p.y);
	dprintf(fd, "p.z = {%f}|\n", p.z);
}
bool	cylinder_intersection(t_minirt *rt, t_ray *ray, const int fd)
{
//	float	a;
//	float	b;
//	float	c;
//	float	disc;

	(void)fd;
//	t_point V = normalizing(rt->Cylinder->cordinates);
//	t_point X = v_sub(ray->origin, rt->Cylinder->cordinates);
//	float a = v_dot(ray->direction, ray->direction) - powf(v_dot(ray->direction, V), 2.0f);
//	float c = v_dot(X, X) - powf(v_dot(X, V), 2.0f) - powf(rt->Cylinder->redius, 2.0f);
//	float b = 2.0f * (v_dot(ray->direction, X) - v_dot(ray->direction, V) * v_dot(X, V));
//	float desc = -b - sqrtf(powf(b, 2.0f) - 4 * a * c);
//	if (desc > EPSILON)
//		return false;
//	return true;
	 float a = powf(ray->direction.x, 2.0f) + powf(ray->direction.z, 2.0f);
	 float b = 2.0f * ray->origin.x * ray->direction.x + 2.0 * ray->origin.z * ray->direction.z;
	 float c = powf(ray->origin.x, 2.0) + powf(ray->origin.z, 2) - rt->Cylinder->redius; // they put 1 i don't know why
	 float disc = powf(b, 2) - 4 * a * c;
	 // ? if the disc is equals to 0  the ray does not intersect with the cylinder
			 if (disc < EPSILON)
		 	return false;
	 return true;
}
//	float r = rt->Cylinder->diameter / 2;
	/*
	 * float a = powf(ray->direction.x, 2.0) + powf(ray->direction.z, 2.0);
	* float b = 2.0 * ray->origin.x * ray->direction.x + 2.0 * ray->origin.z * ray->direction.z;
	* float c = powf(ray->origin.x, 2.0) + powf(ray->origin.z, 2) - rt->Cylinder->redius; // they put 1 i don't know why
	* float disc = powf(b, 2) - 4 * a * c;
	* // ? if the disc is equals to 0  the ray does not intersect with the cylinder
	* if (disc < EPSILON)
	* 	return false;
	* return true;*/

	/*
	 *  A  = C + V*m
	 *  L = C+V*maxim
	 *  Definition:
	 *  	* C is the start cap point of the cylinder
	 *  	* V is a unit length vector that determines the cylinder axis
	 *  	* r is the cylinder's radius
	 *  	* maxim determines the cylinder end cap point
	 *  	and to hit a cylinder we notice that :
	 *  			* A = C * V*m
	 *  			( P - A).V = 0
	 *  				len(P-A) = r
	 		! **   P = o + D*t
	 		! **   substitution for P equation ⤵︎⤵︎⤵︎
	 				!	P - C - D*t + X
						?  * where ~ C is a center point of a Cylinder and ~ X equals to (O - C)
						?  * O - C : subtract the center of the Cylinder from the ray origin to turn the problem into a (0, 0, 0)
	 */
