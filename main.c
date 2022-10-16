#include <stdbool.h>
#include "miniRT.h"


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
}

int main(int ac, char **av)
{
	void		*mlx;
	void		*mlx_win;
	t_minirt	*miniRT;
	t_mlx		data_mlx;
//    t_data *Data;
//    int i;

    miniRT = ft_calloc(1, sizeof(t_minirt));
    miniRT->Data = ft_calloc(1, sizeof(t_data));
    if (ac == 2)
    {
        miniRT->file = av[1];
        miniRT->fd = open(miniRT->file, O_RDONLY);
        fill_data(NULL, miniRT->Data, miniRT->fd);
        miniRT->Ambient = ft_calloc(1, sizeof(t_Ambient));
        miniRT->Camera = ft_calloc(1, sizeof(t_Camera));
        miniRT->Light = ft_calloc(1, sizeof(t_Light));
        fill_Info(miniRT);
		mlx = mlx_init();
		mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
		data_mlx.img = mlx_new_image(mlx, 1920, 1080);
		data_mlx.addr = mlx_get_data_addr(data_mlx.img, &data_mlx.bits_per_pixel, &data_mlx.line_length,
									 &data_mlx.endian);
		ray_render(miniRT, data_mlx);
		mlx_put_image_to_window(mlx, mlx_win, data_mlx.img, 0, 0);
		mlx_loop(mlx);
    }
	/*
//   miniRT Data = miniRT->Data;
//    printf("## Data ##\n");
//    while (Data && Data->check_empty == 1)
//    {
//        i = -1;
//        while (Data->pars[++i])
//            printf("|%s|  ", Data->pars[i]);
//        printf ("\n");
//        Data = Data->next;
//    }*/
    free_mini(miniRT);
}

/*

float 	length_squared(t_point p)
{
	return (p.x * p.x + p.y * p.y + p.z * p.z);
}

float length(t_point p){
	return sqrtf (length_squared(p));
}

t_point mul(const float t,  t_point p){
//	t_point_point r;

	p.x *= t;
	p.y *= t;
	p.z *= t;
	return p;
}

t_point division(t_point p, float t){
	return mul(1/t, p);
}

t_point	unit_vector(t_point v){
	return mul(length_squared(v),v);
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
*/
float mul(t_point p0,  t_point p){
	t_point r;

	r.x = p.x * p0.x;
	r.y = p.y * p0.y;
	r.z = p.z * p0.z;
	return r.x + r.y + r.z;
}

unsigned long createRGB(int r, int g, int b)
{
	return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

void	sphere();

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

t_point sub(t_point conter, t_point origin)
{
	t_point p;

	p.x = conter.x - origin.x;
	p.y = conter.y - origin.y;
	p.z = conter.z - origin.z;
	return (p);
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



}



















