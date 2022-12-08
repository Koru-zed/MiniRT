#include "../Include/miniRT.h"

int	check(int r)
{
	if (r > 255)
		return (255);
	else if (r < 0)
		return (0);
	return (r);
}

t_color	mul_color(t_color color, double s)
{
	t_color	l;

	if (s > EPSILON)
	{
		l.r = check(color.r * s);
		l.g = check(color.g * s);
		l.b = check(color.b * s);
		return (l);
	}
	return (color);
}

t_color	add_2colors(t_color obj, t_color obj2)
{
	t_color	c;

	c.r = check((obj.r + obj2.r));
	c.g = check((obj.g + obj2.g));
	c.b = check((obj.b + obj2.b));
	return (c);
}

void	mix_color(t_minirt *rt, t_hit *pHit, t_rgbMaterial *rgbMat)
{
	rgbMat->diffuse_color.r = (int )(rt->light->brightenss \
		* pHit->obj_color.r);
	rgbMat->diffuse_color.g = (int )(rt->light->brightenss \
		* pHit->obj_color.g);
	rgbMat->diffuse_color.b = (int )(rt->light->brightenss \
		* pHit->obj_color.b);
}

t_color	creat_color(size_t r, size_t g, size_t b)
{
	t_color	rgb;

	rgb.r = (int)r;
	rgb.g = (int)g;
	rgb.b = (int)b;
	return (rgb);
}
