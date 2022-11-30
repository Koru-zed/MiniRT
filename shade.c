#include "Include/miniRT.h"

double max(const double a, const double b)
{
	if (a > b)
		return a;
	return b;
//	return (a > b ) ? a : b;
}


double get_diffuse(t_point lDir, t_point normal)
{
	double	cos_angle;

	cos_angle = v_dot(normal, lDir);
//	if (cos_angle < EPSILON)
//		cos_angle = 0.0f;
	return cos_angle;
//	return cos_angle;
}

t_color convert_array2color(const size_t *color)
{
	t_color	c;

	c.r = (int)color[0];
	c.g = (int)color[1];
	c.b = (int)color[2];
	return c;
}

t_color rollBackColor(const t_color color)
{
	t_color c;
	c.r = check(color.r * 255);
	c.g = check(color.g * 255);
	c.b = check(color.b * 255);
	return c;
}

/*int combine_colors(const size_t *am, const double diffuse, t_color objColor, t_minirt *rt)
{
	size_t re[3];
	size_t diff[3];

	diff[0] = (size_t )(diffuse * rt->Light->brightenss * (rt->Ambient->color[0] / 255.0));
	diff[1] = (size_t )(diffuse * rt->Light->brightenss * (rt->Ambient->color[1] / 255.0));
	diff[2] = (size_t )(diffuse * rt->Light->brightenss * (rt->Ambient->color[2] / 255.0));
	re[0] = check(check((am[0] + diff[0]) * objColor.r) * 255);
	re[1] = check(check((am[1]) + diff[1] * objColor.g) * 255);
	re[2] = check(check((am[2]) + diff[2] * objColor.b) * 255);
	return rgb(re);
}*/

t_color mulTwoColor(t_color obj, t_color obj2)
{
	t_color c;

	c.r = check(obj.r * obj2.r);
	c.g = check(obj.g * obj2.g);
	c.b = check(obj.b * obj2.b);
	return c;
}

t_color addTwoColor(t_color obj, t_color obj2)
{
	t_color c;

	c.r = check((obj.r + obj2.r));
	c.g = check((obj.g + obj2.g));
	c.b = check((obj.b + obj2.b));

	return c;
}

t_color creat_color(size_t r, size_t g, size_t b)
{
	t_color	rgb;

	rgb.r = r;
	rgb.g = g;
	rgb.b = b;
	return rgb;
}

void	ft_print_color(t_color c)
{
	dprintf(1, "r=%d | g%d | b%d\n", c.r, c.g, c.b);
}
t_color 	get_ambient_color(t_color ambColor, t_minirt *rt, t_color objColor)
{
	t_color eff_color;

	eff_color.r = (rt->Ambient->ratio * ambColor.r * objColor.r) / 255;
	eff_color.g = (rt->Ambient->ratio * ambColor.g * objColor.g) / 255;
	eff_color.b = (rt->Ambient->ratio * ambColor.b * objColor.b) / 255;
//	printf("******%f\n", rt->Ambient->ratio);
//	ft_print_color(objColor);
//	eff_color = mul_color(ambColor, rt->Ambient->ratio);
//	ambColor = mulTwoColor(eff_color, objColor);
	return eff_color;
}

/*
 *  # after computing and (if appropriate) negating
# the normal vector...
 */
bool	is_shadowed(t_minirt *rt, t_point hit, t_point normal)
{
//	t_point light_dir = v_adding(hit, v_mul(EPSILON, normal));
	t_point lDir = v_sub(rt->Light->cordinates, hit);
//	lDir = v_mul(-1., lDir);
	double len = length_squared(lDir);
//	t_point dir = normalizing(lDir);
	t_ray ray;
	ray.origin = hit;//v_adding(hit, v_mul(EPSILON, normal));
	ray.direction = lDir;
	t_hit *h = malloc(sizeof(t_hit));
	double t;
	iterate_over_objects(rt, ray, &t, &h);
	if (t > EPSILON && len > t)
		return true;
//	if (intersectRaySphere(r, rt, &t, &h) && t < distance)
//		return true;
	return false;
}

bool	add_light(t_hit *pHit, t_minirt *rt, int *c)
{
//	t_color diffuse_color;
////	t_color eff_color;
//	t_color objColor;
	t_color ambColor;
	t_rgbMaterial	*rgbMat;
	t_point lDir;
	double i = 0.0f;
	double diffuse = 0.f;

	ambColor = convert_array2color(rt->Ambient->color);
	rgbMat = malloc(sizeof(t_rgbMaterial));
	if (!rgbMat)
		exit(EXIT_FAILURE);
//	pHit->hit_pos = v_mul(EPSILON, pHit->hit_pos);
	lDir = normalizing(v_sub(rt->Light->cordinates, pHit->hit_pos));
	ambColor = get_ambient_color(ambColor, rt, pHit->obj_color);
	diffuse = get_diffuse(lDir, pHit->normal);
	if (is_shadowed(rt, pHit->hit_pos, pHit->normal) || diffuse < EPSILON)
	{
		rgbMat->diffuse_color = creat_color(0, 0, 0);
	}
	else
	{
		rgbMat->diffuse_color.r = (rt->Light->brightenss * pHit->obj_color.r);
		rgbMat->diffuse_color.g = (rt->Light->brightenss * pHit->obj_color.g);
		rgbMat->diffuse_color.b = (rt->Light->brightenss * pHit->obj_color.b);
		rgbMat->diffuse_color = mul_color(rgbMat->diffuse_color,   diffuse);
	}
	rgbMat->eff_color = addTwoColor(ambColor, rgbMat->diffuse_color);
	*c = rgb(rgbMat->eff_color);
	free(rgbMat);
	return true;
}