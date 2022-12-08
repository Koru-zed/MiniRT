# MiniRT

bool intersectDisk(t_ray disk, t_ray ray, double radius) 
{ 
    double t = DBL_MAX;
    if (intersectPlane()) { 
        t_point p = v_adding(ray.origin, v_mul(ray.direction, t)); 
        t_point v = v_sub(p, disk.origin); 
        double d2 = length_squared(v);
        return (d2 <= radius); 
        // or you can use the following optimisation (and precompute radius^2)
        // return d2 <= radius2; // where radius2 = radius * radius
     } 
 
     return false; 
} 

bool	cylinder_intersection(t_minirt *rt, t_ray ray, double *t, t_hit *hit)
{
	int i = -1;
	double t_min;
	double m;

	t_point a;
	t_point B;
	t_point hHat;

	*t = DBL_MAX;
	t_min = DBL_MAX;
	t_Cylinder *cy=  rt->cylinder;
	ray.direction = normalizing(ray.direction);
	while (++i < rt->data->shape.cy)
	{
		a = v_mul(cy[i].height, cy[i].orientation); //to find orign of top
		B = normalizing(a); //to find direction of top
		cy[i].top = v_adding(v_mul(cy[i].height, B), cy[i].cordinates); //find top point
		cy[i].x = v_sub(ray.origin, cy[i].top);
		hHat = normalizing(v_sub(cy[i].top, v_adding(cy[i].top, v_mul(cy[i].height, cy[i].orientation))));
		cy[i].q.a = v_dot(ray.direction, ray.direction) - pow(v_dot(ray.direction, hHat), 2);
		cy[i].q.b = 2 * (v_dot(ray.direction, cy[i].x) - (v_dot(ray.direction, hHat) * v_dot(cy[i].x, hHat)));
		cy[i].q.c = v_dot(cy[i].x, cy[i].x) - pow(v_dot(cy[i].x, hHat), 2) - pow(cy[i].redius, 2);
		cy[i].q.discriminant = pow(cy[i].q.b, 2) - (4 * cy[i].q.a * cy[i].q.c);
		if (cy[i].q.discriminant < EPSILON)
			continue ;
		cy[i].q.sqrt_disc = sqrt(cy[i].q.discriminant);
		t_min = git_root(cy[i], hHat, ray, &m);
		cy[i].top_Disk.ray.origin = top;
		cy[i].top_Disk.ray.direction = hHat;
		if (intersectDisk(cy[i].top_Disk.ray, ray, cy[i].redius))

		if (t_min < *t)
		{
			*t= t_min;
			hit->obj_color = convet((int *)cy[i].color);
			hit->hit_pos = v_adding(cy[i].top, v_mul(m, hHat));
			hit->normal = normalizing(v_sub(hit->hit_pos, v_sub(cy[i].top, v_mul(m, hHat))));
			if (rt->mlx->mouse)
				rt->mlx->obj.index = i;
		}
	}
	if (*t == DBL_MAX)
		return false;
	return true;
}