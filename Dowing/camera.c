#include "../Include/miniRT.h"

t_matrix    new_matrix(t_point origin, t_point forward, t_point right, t_point up)
{
    t_matrix	new;

	new.d[0][0] = right.x;
	new.d[0][1] = right.y;
	new.d[0][2] = right.z;
	new.d[0][3] = 0;
	new.d[1][0] = up.x;
	new.d[1][1] = up.y;
	new.d[1][2] = up.z;
	new.d[1][3] = 0;
	new.d[2][0] = forward.x;
	new.d[2][1] = forward.y;
	new.d[2][2] = forward.z;
	new.d[2][3] = 0;
	new.d[3][0] = origin.x;
	new.d[3][1] = origin.y;
	new.d[3][2] = origin.z;
	new.d[3][3] = 1;
	return (new);
}


void    fill_matrix(t_Camera *_camera)
{
    t_point random;
    t_point right;
    t_point up;

    random =  new_point(0, 1, 0);
    right = normalizing(v_cross(random, _camera->direction));
    up = normalizing(v_cross(_camera->direction, right));
    _camera->matrix.M = new_matrix(right, up, _camera->ray.direction, _camera->ray.origin);
}