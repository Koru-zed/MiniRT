#include "Include/miniRT.h"

//int *getColorAmbient()

int check(int r)
{
	if (r > 255)
		return 255;
	else if (r < 0)
		return 0;
	return r;
}

t_color  mul_color(t_color color, double s)
{
	t_color l;

	if (s > EPSILON) {

		l.r = check(color.r * s);
		l.g = check(color.g * s);
		l.b = check(color.b * s);
		return l;
	}
	return color;
}