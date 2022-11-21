#include "../Include/miniRT.h"

// t_matrix    new_matrix(t_point origin, t_point forward, t_point right, t_point up)
// {
//     t_matrix	new;

// 	new.M[0][0] = right.x;
// 	new.M[0][1] = right.y;
// 	new.M[0][2] = right.z;
// 	new.M[0][3] = 0;
// 	new.M[1][0] = up.x;
// 	new.M[1][1] = up.y;
// 	new.M[1][2] = up.z;
// 	new.M[1][3] = 0;
// 	new.M[2][0] = forward.x;
// 	new.M[2][1] = forward.y;
// 	new.M[2][2] = forward.z;
// 	new.M[2][3] = 0;
// 	new.M[3][0] = origin.x;
// 	new.M[3][1] = origin.y;
// 	new.M[3][2] = origin.z;
// 	new.M[3][3] = 1;
// 	return (new);
// }

t_matrix    new_matrix(t_point u, t_point v, t_point w, t_point T)
{
    t_matrix	new;

	new.M[0][0] = u.x;
	new.M[1][0] = u.y;
	new.M[2][0] = u.z;
	new.M[3][0] = 0;
	new.M[0][1] = v.x;
	new.M[1][1] = v.y;
	new.M[2][1] = v.z;
	new.M[3][1] = 0;
	new.M[0][2] = w.x;
	new.M[1][2] = w.y;
	new.M[2][2] = w.z;
	new.M[3][2] = 0;
	new.M[0][3] = T.x;
	new.M[1][3] = T.y;
	new.M[2][3] = T.z;
	new.M[3][3] = 1;
	return (new);
}

// void    fill_matrix(t_Camera *_camera)
// {
//     t_point random;
//     t_point right;
//     t_point up;

//     random =  new_point(0, 1, 0);

//     right = normalizing(v_cross(random, _camera->ray.direction));
//     up = normalizing(v_cross(_camera->ray.direction, right));
//     _camera->matrix = new_matrix(_camera->ray.origin, _camera->ray.direction, right, up);

// }

void    fill_matrix(t_Camera *_camera)
{
    t_point w;
    t_point u;
	t_point v;
    t_point up;

    up =  new_point(0, 1, 0);
	w = normalizing(v_sub(_camera->ray.origin, _camera->ray.direction));
    u = normalizing(v_cross(up, w));
    v = v_cross(w, u);
    _camera->matrix = new_matrix(u, v, w, _camera->ray.direction);
}