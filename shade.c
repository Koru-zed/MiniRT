#include "Include/miniRT.h"

float max(const float a, const float b)
{
	if (a > b)
		return a;
	return b;
//	return (a > b ) ? a : b;
}

//	normal * 2 * dot(in, normal)
t_point reflect(t_point normal, t_point in)
{
	t_point new;

	new = v_mul(v_dot(in, normal), v_mul(2.0f, normal));
	return new;
}


float get_diffuse(t_point lDir, t_point normal, t_minirt *rt)
{
	float	cos_angle;

	cos_angle = v_dot(lDir, normal);
//	if (cos_angle < EPSILON)
//		cos_angle = 0.0f;
	return cos_angle;
//	return cos_angle;
}

t_color convert_array2color(const size_t *color)
{
	t_color	c;

	c.r = (int)color[0] / 255;
	c.g = (int)color[1] / 255;
	c.b = (int)color[2] / 255;
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

/*int combine_colors(const size_t *am, const float diffuse, t_color objColor, t_minirt *rt)
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

	c.r = obj.r * obj2.r;
	c.g = obj.g * obj2.g;
	c.b = obj.b * obj2.b;
	return c;
}

t_color addTwoColor(t_color obj, t_color obj2)
{
	t_color c;

	c.r = obj.r + obj2.r;
	c.g = obj.g + obj2.g;
	c.b = obj.b + obj2.b;
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
t_color 	get_ambient_color(t_color ambColor, t_minirt *rt, t_color objColor)
{
	t_color eff_color;
	t_color color;

	eff_color = mul_color(ambColor, rt->Ambient->ratio);
	ambColor = mulTwoColor(eff_color, objColor);
//	color.r = (size_t )((float )ambientColor.r * ratio);
//	color.g = (size_t )((float )ambientColor.g * ratio);
//	color.b = (size_t )((float )ambientColor.b * ratio);
//	printf("r = %zu\t g = %zu \tb=%zu\n", color.r, color.g, color.b);
	return ambColor;
}

bool	add_light(t_hit *pHit, t_minirt *rt, int *c, float *intensity)
{
//	t_color diffuse_color;
//	t_color eff_color;
//	t_color objColor;
//	t_color ambColor;
	t_rgbMaterial	*rgbMat;
	t_point lDir;
	float i = 0.0f;
	float diffuse = 0.f;

	rgbMat = malloc(sizeof(t_rgbMaterial));
	if (!rgbMat)
		exit(EXIT_FAILURE);
	lDir = normalizing(v_sub(rt->Light->cordinates, pHit->hit_pos));
/*	eff_color = mul_color(objColor, rt->Light->brightenss);
	ambColor = get_ambient_color(ambColor, rt, objColor);
	diffuse = get_diffuse(lDir, pHit->normal, rt);
	if (diffuse < EPSILON)
		diffuse_color = creat_color(0, 0, 0);
	else
	{
		diffuse_color = mul_color(eff_color, diffuse);
//		diffuse_color = mul_color(ambColor, diffuse);
	}
	eff_color = addTwoColor(ambColor, diffuse_color);
	*c = rgb(convert_color2array(eff_color));*/
	return true;
}
/*	if (diffuse > EPSILON) {

//		diffuse += + rt->Light->brightenss * diffuse / (length_squared(pHit->normal) * length_squared(lDir));
	}
	diffuse += rt->Ambient->ratio;
//	printf("dif %f\n", diffuse);
	pHit->color[0] *= diffuse;
	pHit->color[1] *= diffuse;
	pHit->color[2] *= diffuse;
	effective_color = mul_color(rt->Ambient->color, diffuse);
	effective_color[0] = Ambient[0] + effective_color[0];
	effective_color[1] = Ambient[1] + effective_color[1];
	effective_color[2] = Ambient[2] + effective_color[2];*/
//	*c = mul_color(pHit->color, diffuse);
//	printf("%d\n", *c);
//	if (angle < EPSILON)
//	{
//		diffuse = 0.0f;
//	}
//	if (angle > 1.5708f)
//	{
//		// No illumination
//		*intensity = 0.0f;
//		*c = BLACK;
//		return false;
//	}
//	printf("angel =%f\n", angle);
//	*intensity = rt->Light->brightenss * (1.0f - (angle / 1.5708f));
//	pHit->color[0] *=  (size_t )(rt->Light->brightenss * 1.0f - (angle));// / 1.5708f)));
//	pHit->color[1] = (size_t )(rt->Light->brightenss * 1.0f - angle);//(angle / 1.5708f)));
//	pHit->color[2] = (size_t )(rt->Light->brightenss * 1.0f - angle);//(angle / 1.5708f)));
//	*c = rgb(pHit->color);