///* A simple ray tracer - part 1 */
//
//#include <stdio.h>
//#include <stdbool.h> /* Needed for boolean datatype */
//#include "Include/miniRT.h"
//
//
///* The vector structure */
//typedef struct{
//      float x,y,z;
//}vector;
//
///* The sphere */
//typedef struct{
//        vector pos;
//        float  radius;
//}sphere;
//
///* The ray */
//typedef struct{
//        vector start;
//        vector dir;
//}ray;
//
///* Subtract two vectors and return the resulting vector */
//vector vectorSub(vector *v1, vector *v2){
//	vector result = {v1->x - v2->x, v1->y - v2->y, v1->z - v2->z };
//	return result;
//}
//
///* Multiply two vectors and return the resulting scalar (dot product) */
//float vectorDot(vector *v1, vector *v2){
//	return v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
//}
//
//
///* Check if the ray and sphere intersect */
//bool intersectRaySphere(ray *r, sphere *s){
//
//	/* A = d.d, the vector dot product of the direction */
//	float A = vectorDot(&r->dir, &r->dir);
//
//	/* We need a vector representing the distance between the start of
//	 * the ray and the position of the circle.
//	 * This is the term (p0 - c)
//	 */
//	vector dist = vectorSub(&r->start, &s->pos);
//
//	/* 2d.(p0 - c) */
//	float B = 2 * vectorDot(&r->dir, &dist);
//
//	/* (p0 - c).(p0 - c) - r^2 */
//	float C = vectorDot(&dist, &dist) - (s->radius * s->radius);
//
//	/* Solving the discriminant */
//	float discr = B * B - 4 * A * C;
//
//	/* If the discriminant is negative, there are no real roots.
//	 * Return false in that case as the ray misses the sphere.
//	 * Return true in all other cases (can be one or two intersections)
//	 */
//	if(discr < 0)
//		return false;
//	else
//		return true;
//}
//
//
//int main(){
//	t_minirt *miniRT;
//	miniRT = ft_calloc(1, sizeof(t_minirt));
//	/* Our ray and a sphere */
//	sphere s;
//	ray r;
//
//	/* x, y for screen 'resolution' */
//	int x,y;
//
//	/* Intersect ray/sphere or not */
//	bool hit;
//
//	/* Position the sphere */
//	s.pos.x = 100.0;
//	s.pos.y = 100.0;
//	s.pos.z = 20.6;
//
//	/* Sphere radius */
//	s.radius = 100;
//
//	/* Direction of the ray */
//	r.dir.x = 0.0;
//	r.dir.y = 0.0;
//	r.dir.z = -10.0;
//
//	/* Start position of the ray, z coordinate */
//	r.start.z = 100;
//
//	/* Iterate over every 'pixel' of our screen
//	 * We use a 40x40 virtual ASCII screen for now
//	 */
//	miniRT->Mlx = ft_calloc(1, sizeof(t_mlx));
//	miniRT->Mlx->mlx = mlx_init();
//	miniRT->Mlx->win = mlx_new_window(miniRT->Mlx->mlx, 720, 540, "miniRT");
//	miniRT->Mlx->img = mlx_new_image(miniRT->Mlx->mlx, 720, 540);
//	miniRT->Mlx->addr = mlx_get_data_addr(miniRT->Mlx->img, &miniRT->Mlx->bits_per_pixel, &miniRT->Mlx->line_length, &miniRT->Mlx->endian);
//
//	for(y=0;y<540;y++){
//		/* Set the y-coordinate of the start position of the ray */
//		r.start.y = y;
//		for(x=0;x<720;x++){
//			/* Set the x-coordinate of the start position of the ray */
//			r.start.x = x;
//
//			/* Check if the ray intersects with the shpere */
//			hit = intersectRaySphere(&r, &s);
//			if(hit)
//				my_mlx_pixel_put(miniRT->Mlx, x, y, 0xFFFF00);
//			else
//				my_mlx_pixel_put(miniRT->Mlx, x, y, 0x000033);
//		}
//		/* First row of the screen done, move to next row */
//
//	}
//	mlx_put_image_to_window(miniRT->Mlx->mlx, miniRT->Mlx->win, miniRT->Mlx->img, 0, 0);
//	mlx_loop(miniRT->Mlx->mlx);
//}
