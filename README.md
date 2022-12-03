# MiniRT

bool	cylinder_intersection(t_minirt *rt, t_ray ray, double *t, int *color)
{
	int i = -1;
	double t_min;

	*t = FLT_MAX;
	t_min = FLT_MAX;
	t_Cylinder *cy=  rt->Cylinder;
	while (++i < rt->Data->shape.cy)
	{
		// t_point A = v_mul(cy[i].height, cy[i].orientation); //to find orign of top
		// t_point B = normalizing(A); //to find direction of top 
		// t_point top = v_mul(cy[i].height, B); //find top point
		// double h_2 = cy[i].height * cy[i].height; 
		// t_point ro = v_sub(ray.origin, cy[i].cordinates);
		// double a = h_2 - v_dot(top, ray.direction) * v_dot(top, ray.direction);
		// double b = h_2 * v_dot(ro, ray.direction) - v_dot(top, ro) * v_dot(top, ray.direction);
		// double c = h_2 * v_dot(ro, ro) - v_dot(top, ro)
		// 								* v_dot(top, ro) - (cy[i].redius) * (cy[i].redius) * h_2;
		
		t_point A = v_mul(cy[i].height, cy[i].orientation); //to find orign of top
		t_point B = normalizing(A); //to find direction of top 
		t_point top = v_mul(cy[i].height, B); //find top point
		// Clear 
		
		t_point X = v_sub(ray.origin, top);
		double a = v_dot(ray.direction, ray.direction) - powf(v_dot(ray.direction, cy[i].orientation), 2);
		double b = 2 * (v_dot(ray.direction, X) - (v_dot(ray.direction, cy[i].orientation) * v_dot(X, cy[i].orientation)));
		double c = v_dot(X, X) - powf(v_dot(X, cy[i].orientation), 2) - powf(cy[i].redius, 2);
		double discriminant = powf(b, 2) - (4 * a * c);
		if (discriminant < EPSILON)
			continue ;
		t_min = get_root(discriminant, b, a);
		double m = (v_dot(ray.direction, v_mul(t_min, cy[i].orientation))) + v_dot(X, cy[i].orientation);
		if (m > EPSILON && m <= cy[i].height)
		{
			t_point p = v_adding(ray.origin, v_mul(t_min, ray.direction));
			if (v_dot(v_sub(v_sub(p , top), v_mul(m, cy[i].orientation)), cy[i].orientation) < EPSILON)
			{
			t_point center = v_adding(top, v_mul(m, cy[i].orientation));
			double N = v_dot(v_sub(p, center), cy[i].orientation);
			double M = length_squared(v_sub(p, center));
			if ((M == cy[i].redius) && (N < EPSILON && N > -EPSILON))
			{
				if (t_min < *t)
				{
					*t= t_min;
					*color = rgb(cy[i].color);
					if (rt->Mlx->mouse)
						rt->Mlx->obj.index = i;
				}
			}
			}
		}
	}
	if (*t == FLT_MAX)
		return false;
	else
 		return true;
}