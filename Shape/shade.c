#include "../Include/miniRT.h"

double	get_diffuse(t_point lDir, t_point normal)
{
	double	cos_angle;

	cos_angle = v_dot(normal, lDir);
	return (cos_angle);
}

t_color	convert_array2color(const size_t *color)
{
	t_color	c;

	c.r = (int)color[0];
	c.g = (int)color[1];
	c.b = (int)color[2];
	return (c);
}

t_color	get_ambient_color(t_color ambColor, t_minirt *rt, t_color objColor)
{
	t_color	eff_color;

	eff_color.r = (int)(rt->Ambient->ratio * ambColor.r * objColor.r) / 255;
	eff_color.g = (int)(rt->Ambient->ratio * ambColor.g * objColor.g) / 255;
	eff_color.b = (int)(rt->Ambient->ratio * ambColor.b * objColor.b) / 255;
	return (eff_color);
}

bool	is_shadowed(t_minirt *rt, t_point hit, t_point normal)
{
	t_ray	ray;
	t_hit	*h;
	t_point	l_dit;
	double	t;
	double	len;

	l_dit = v_sub(rt->Light->cordinates, hit);
	len = length_squared(l_dit);
	ray.origin = v_adding(hit, v_mul(EPSILON, normal));
	ray.direction = l_dit;
	h = malloc(sizeof(t_hit));
	iterate_over_objects(rt, ray, &t, &h);
	if ((t > EPSILON && len > t) || fabs(len - t) < EPSILON)
		return (true);
	return (false);
}

bool	add_light(t_hit *pHit, t_minirt *rt, int *c)
{
	t_color			amb_color;
	t_rgbMaterial	*rgb_mat;
	t_point			l_dit;
	double			diffuse;

	amb_color = convert_array2color(rt->Ambient->color);
	rgb_mat = malloc(sizeof(t_rgbMaterial));
	if (!rgb_mat)
		exit(EXIT_FAILURE);
	l_dit = normalizing(v_sub(rt->Light->cordinates, pHit->hit_pos));
	amb_color = get_ambient_color(amb_color, rt, pHit->obj_color);
	diffuse = get_diffuse(l_dit, pHit->normal);
	if (is_shadowed(rt, pHit->hit_pos, pHit->normal) || diffuse < EPSILON)
		rgb_mat->diffuse_color = creat_color(0, 0, 0);
	else
	{
		mix_color(rt, pHit, rgb_mat);
		rgb_mat->diffuse_color = mul_color(rgb_mat->diffuse_color, diffuse);
	}
	rgb_mat->eff_color = add_2colors(amb_color, rgb_mat->diffuse_color);
	*c = rgb(rgb_mat->eff_color);
	free(rgb_mat);
	return (true);
}
