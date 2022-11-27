#include "Include/miniRT.h"

//int *getColorAmbient()

int check(int r)
{
	if (r > 255)
		return 255;
	return r;
}

t_color  mul_color(t_color color, float s)
{
	t_color l;

	if (s > EPSILON) {

		l.r = check(color.r * s);
		l.g = check(color.r * s);
		l.b = check(color.r * s);
		return l;
	}
	return color;
}