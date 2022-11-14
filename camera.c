//#include "Include/miniRT.h"
//
///*
//  * we need FOV (field of view)
// * and aspect ratio = w/h == w =  width / height
//
// *  field of view depends of sensor size and
// *  the equation is FOV = 2 tan^-1 (h/2f)
// */
//
//t_minirt *perspective_camera(t_point origin, t_point target, t_point up_guide, t_minirt *rt, float aspectRatio)
//{
//	rt->Camera->forward = normalizing(sub(target, origin));
//	rt->Camera->right = normalizing(cross(rt->Camera->forward, up_guide));
//	rt->Camera->up = cross(rt->Camera->right, rt->Camera->forward);
//	rt->Camera->h = tan((double ) rt->Camera->fov);
//	rt->Camera->w = rt->Camera->h * aspectRatio;
//	return rt;
//}
//
//t_ray	init_ray(t_point origin, t_point dir)
//{
//	t_ray	r;
//
//	r.origin = origin;
//	r.dir = dir;
//	return r;
//}
//
//t_ray	makeRay(t_minirt *rt, t_point p)
//{
//	// * dir = forward + ( (p.u * w) * right ) + ( (p.v * h) * up )
//	float tmp = rt->Camera->w * p.x;
//	t_point tmp1 = mul(tmp , rt->Camera->right);
//	float tmp2 = rt->Camera->h * p.y;
//	t_point tmp3 = mul(tmp2, rt->Camera->up);
//
//	t_point s = adding(rt->Camera->forward, tmp1);
//	t_point dir = adding(s, tmp3);
//	return init_ray(convert_to_point(rt->Camera->cordinates), normalizing(dir));
//}
//
//void	world_camera()
//{
//
//}å