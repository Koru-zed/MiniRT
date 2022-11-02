/* A simple ray tracer - part 1 */

#include <stdio.h>
#include <stdbool.h> /* Needed for boolean datatype */
#include "Include/miniRT.h"
// #include <mlx.h>
/* The vector structure */
typedef struct{
      float x,y,z;
}vector;

/* The sphere */
typedef struct{
        vector pos;
        float  radius;
}sphere; 

/* The ray */
typedef struct{
        vector start;
        vector dir;
}ray;

/* Subtract two vectors and return the resulting vector */
vector vectorSub(vector *v1, vector *v2){
	vector result = {v1->x - v2->x, v1->y - v2->y, v1->z - v2->z };
	return result;
}

/* Multiply two vectors and return the resulting scalar (dot product) */
float vectorDot(vector *v1, vector *v2){
	return v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
}

static void	my_mlx_pixel_put(t_mlx *Mlx, int x, int y, int color)
{
	char	*dst;

	dst = Mlx->addr + (y * Mlx->line_length + x * (Mlx->bits_per_pixel >> 3));
	*(unsigned int*)dst = color;
}

/* Check if the ray and sphere intersect */
bool intersectRaySphere(ray *r, sphere *s){
	
	/* A = d.d, the vector dot product of the direction */
	float A = vectorDot(&r->dir, &r->dir); 
	
	/* We need a vector representing the distance between the start of 
	 * the ray and the position of the circle.
	 * This is the term (p0 - c) 
	 */
	vector dist = vectorSub(&r->start, &s->pos);
	
	/* 2d.(p0 - c) */  
	float B = 2 * vectorDot(&r->dir, &dist);
	
	/* (p0 - c).(p0 - c) - r^2 */
	float C = vectorDot(&dist, &dist) - (s->radius * s->radius);
	
	/* Solving the discriminant */
	float discr = B * B - 4 * A * C;
	
	/* If the discriminant is negative, there are no real roots.
	 * Return false in that case as the ray misses the sphere.
	 * Return true in all other cases (can be one or two intersections)
	 */
	if(discr < 0)
		return false;
	else
		return true;
}


int main(){
	
	/* Our ray and a sphere */
	sphere s;
	ray r;
    	size_t t;
	// int y;
    t_mlx *Mlx;
    // t_data *Data;
	/* x, y for screen 'resolution' */
	int x,y;	

	/* Intersect ray/sphere or not */
	bool hit;

	/* Position the sphere */
	s.pos.x = 50;
	s.pos.y = 50;
	s.pos.z = 20.6;

	/* Sphere radius */
	s.radius = 6.3;

	/* Direction of the ray */
	r.dir.x = -50;
	r.dir.y = 0;
	r.dir.z = 20;

	/* Start position of the ray, z coordinate */
	r.start.z = 0;


    Mlx = ft_calloc(1, sizeof(t_mlx));
    Mlx->mlx = mlx_init();
    Mlx->win = mlx_new_window(Mlx->mlx, 720, 540, "miniRT");
    Mlx->img = mlx_new_image(Mlx->mlx, 720, 540);
    Mlx->addr = mlx_get_data_addr(Mlx->img, &Mlx->bits_per_pixel, &Mlx->line_length, &Mlx->endian);

	/* Iterate over every 'pixel' of our screen
	 * We use a 40x40 virtual ASCII screen for now
	 */
	for(y=0;y<540;y++){
		/* Set the y-coordinate of the start position of the ray */
		r.start.y = y; 
		for(x=0;x<720;x++){
			/* Set the x-coordinate of the start position of the ray */
			r.start.x = x;

			/* Check if the ray intersects with the shpere */
			hit = intersectRaySphere(&r, &s);
			if (hit)
				my_mlx_pixel_put(Mlx, x, y, 0xFF3333);
			else
				my_mlx_pixel_put(Mlx, x, y, 0xFFFFFF);
		}
		/* First row of the screen done, move to next row */
	}
    mlx_put_image_to_window(Mlx->mlx, Mlx->win, Mlx->img, 0, 0);
    mlx_loop(Mlx->mlx);

}