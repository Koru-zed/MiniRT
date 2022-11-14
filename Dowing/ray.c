#include "../Include/miniRT.h"

t_point point_dir(t_ray *ray)
{
    t_point point;

    point = mul(ray->direction, ray->t);
    point = adding(point, ray->origin);
    return  point;
}

