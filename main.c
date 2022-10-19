#include "Include/miniRT.h"
# include <sys/time.h>
#include <stdbool.h>

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

/*
void ray_render(t_minirt *minirt, t_mlx mlx);

void	my_mlx_pixel_put(t_mlx *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw(t_vector v, t_mlx data)
{
	int		steps;
	int		dx;
	int		dy;
	float	x_inc;
	float	y_inc;

	dx = v.x[1] - v.x[0];
	dy = v.y[1] - v.y[0];
	float xf = (float) v.x[0];
	float yf = (float) v.y[0] ;
	if (abs(dx) > abs(dy))
		steps = abs(dx);
	else
		steps = abs(dy);
	x_inc = (float)dx / (float)steps;
	y_inc = (float)dy / (float)steps;
	dx = -1;
	while (++dx <= steps)
	{
		my_mlx_pixel_put(&data, (int)roundf(xf),
						 (int)roundf(yf), RED);
		xf += x_inc;
		yf += y_inc;
	}
}*/

int main(int ac, char **av)
{
	size_t t;
	// int y;
    t_minirt *miniRT;

    // t_data *Data;

    (void)ac;
    (void)av;
    miniRT = ft_calloc(1, sizeof(t_minirt));
    // miniRT->Data = ft_calloc(1, sizeof(t_data));
    // if (av[1])
    // {
    //     miniRT->file = av[1];
    //     miniRT->fd = open(miniRT->file, O_RDONLY);
    //     fill_data(miniRT->Data, miniRT->fd);
    //     miniRT->Ambient = ft_calloc(1, sizeof(t_Ambient));
    //     miniRT->Camera = ft_calloc(1, sizeof(t_Camera));
    //     miniRT->Light = ft_calloc(1, sizeof(t_Light));
    //     fill_Info(miniRT);
    // }
    miniRT->Mlx = ft_calloc(1, sizeof(t_mlx));
    miniRT->Mlx->mlx = mlx_init();
    miniRT->Mlx->win = mlx_new_window(miniRT->Mlx->mlx, 720, 540, "miniRT");
    miniRT->Mlx->img = mlx_new_image(miniRT->Mlx->mlx, 720, 540);
    miniRT->Mlx->addr = mlx_get_data_addr(miniRT->Mlx->img, &miniRT->Mlx->bits_per_pixel, &miniRT->Mlx->line_length, &miniRT->Mlx->endian);
	t = get_time();
	miniRT->Mlx->y[0]= 59;
	while (miniRT->Mlx->y[0]++ < 300)
	{
    	draw_line(miniRT->Mlx);
	// draw(miniRT->Mlx, y);
		printf ("y[0] = [%d]\n", miniRT->Mlx->y[0]);
	}
	printf ("-----------------------\n");
	printf("Time measured: %lld ms.\n", get_time() - t);
    mlx_put_image_to_window(miniRT->Mlx->mlx, miniRT->Mlx->win, miniRT->Mlx->img, 0, 0);
    mlx_loop(miniRT->Mlx->mlx);
    free_mini(miniRT);
}

float 	length_squared(t_point p)
{
	return (p.x * p.x + p.y * p.y + p.z * p.z);
}

float length(t_point p){
	return sqrtf (length_squared(p));
}


unsigned long createRGB(double r, double g, double b)
{
	int ir = (int)(255.999 * r);
	int ig = (int)(255.999 * g);
	int ib = (int)(255.999 * b);
	return (ir << (16 + ig) << (8 + ib));
}

t_point sub(t_point center, t_point origin)
{
	t_point p;

	p.x = center.x - origin.x;
	p.y = center.y - origin.y;
	p.z = center.z - origin.z;
	return (p);
}

t_point	adding(t_point p, t_point v)
{
	p.x += v.x;
	p.y += v.y;
	p.z += v.z;
	return p;
}

float mull(t_point p0,  t_point p) {
	t_point r;

	r.x = p.x * p0.x;
	r.y = p.y * p0.y;
	r.z = p.z * p0.z;
	return r.x + r.y + r.z;
}

t_point mul(const float t,  t_point p){
	p.x *= t;
	p.y *= t;
	p.z *= t;
	return p;
}

t_point division(t_point p, float t){
	return mul(1/t, p);
}

t_point	cross(const t_point u, const t_point v) {
	t_point vec;
	vec.x = u.y * v.z - u.z * v.y;
	vec.y = u.z * v.x - u.x * v.z;
	vec.z = u.x * v.y - u.y * v.x;
	return vec;
}

float	dot(const t_point u, const t_point v)
{
	return u.x * v.x
		   + u.y * v.y
		   + u.z * v.z;
}

t_point	unit_vector(t_point v){
	return mul(length_squared(v),v);
}

/*void	sphere(t_mlx mlx) {
	const int image_width = 256;
	const int image_height = 256;
	for (int j = image_height - 1; j >= 0; --j) {
		for (int i = 0; i < image_width; ++i) {
			double r = (double) i / (image_width - 1);
			double g = (double) j / (image_height - 1);
			double b = 0.25;
			int color = (int) createRGB(r, g, b);
			my_mlx_pixel_put(&mlx, i, j, color);
		}
	}
}*/

/*
 * Let's make:
		* $ A = \vec d.\vec d $
		* $ B = 2\vec d.(\vec p_0 - \vec c) $
		* $ C = (\vec p_0 - \vec c).(\vec p_0 - \vec c) - r^2 $
 */
/*
		  *  We need a vector representing the distance between the start of
 				 * the ray and the position of the circle. < dist >
         *
         *
*/
bool	intersectRaySphere(t_ray *r, t_sphere *s)
{
	float	A;
	t_point	dist;

	A = dot(r->dir, r->dir);
	dist = sub(r->start, s->pos);
	float B = 2 * dot(dist, dist);
	float C = dot(dist, dist) - (s->radius * s->radius);
	/* * Solving the discriminant */
	float discr = B * B - 4 * A * C;
	/* * If the discriminant is negative, there are no real roots.
	  * Return false in that case as the ray misses the sphere.
	  * Return true in all other cases (can be one or two intersections)
	  */
	if (discr < 0)
		return false;
	return true;
}
/*



void ray_render(t_minirt *minirt, t_mlx mlx)
{
	(void) minirt;
	(void) mlx;
	const int image_width = 1000;
	const int image_height = 1000;

	// Render


	for (int j = image_height-1; j >= 0; --j) {
		for (int i = 0; i < image_width; ++i) {
			double r = (double)i / (image_width-1);
			double g = (double)j / (image_height-1);
			double b = 0.25;

			int ir = (int)(255.999 * r);
			int ig = (int)(255.999 * g);
			int ib = (int)(255.999 * b);
			int color = (int)createRGB(ir, ig, ib);
			my_mlx_pixel_put(&mlx, i, j, color);
		}
	}

}

bool	ray_interesct(const t_point origin, const t_point dir, float *t, t_point center, float r)
{
	t_point	L;
	float	tca;
	float	d2;
	float	thc;
	float	t0;

	L = sub(center, origin);
	tca = mul(L, dir);
	d2 = mul(L, L) - tca * tca;
	thc = sqrtf(r * r - d2);
	*t = tca - thc;
	t0 = tca + thc;
	if (*t < 0)
		*t = t0;
	if (*t < 0)
		return false;
	return true;
}

void	sphere()
{
	float	radius;
	t_vector center;



}*/



















