#include "Include/miniRT.h"

t_matrix    new_matrix(t_point right,  t_point up, t_point forward, t_point origin)
{
    t_matrix	new;

	new.M[0][0] = right.x;
	new.M[0][1] = right.y;
	new.M[0][2] = right.z;
	new.M[0][3] = 0;
	new.M[1][0] = up.x;
	new.M[1][1] = up.y;
	new.M[1][2] = up.z;
	new.M[1][3] = 0;
	new.M[2][0] = forward.x;
	new.M[2][1] = forward.y;
	new.M[2][2] = forward.z;
	new.M[2][3] = 0;
	new.M[3][0] = origin.x;
	new.M[3][1] = origin.y;
	new.M[3][2] = origin.z;
	new.M[3][3] = 1;
	return (new);
}

t_matrix	dir_matrix(void)
{
	t_point forward;
    t_point origin;
    t_point right;
    t_point up;

	right = new_point(1, 0, 0);
	up = new_point(0, 1, 0);
	forward = new_point(0, 0, 1);
	origin = new_point(0, 0, 0);
	return new_matrix(right, up, forward, origin);
}

void    camera_matrix(t_Camera *_camera)
{
    t_point right;
    t_point up;

    right = normalizing(v_cross(new_point(0, 1, 0), _camera->ray.direction));
    up = normalizing(v_cross(_camera->ray.direction, right));
    _camera->matrix = new_matrix(right, up, _camera->ray.direction, _camera->ray.origin);
}
