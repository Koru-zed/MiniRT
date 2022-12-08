#include "../Include/miniRT.h"

t_point	new_point(double x, double y, double z)
{
	t_point	pos;

	pos.x = x;
	pos.y = y;
	pos.z = z;
	return (pos);
}

t_color	add_color(const size_t *c)
{
	t_color	obj;

	obj.r = (int)c[0];
	obj.g = (int)c[1];
	obj.b = (int)c[2];
	return (obj);
}
