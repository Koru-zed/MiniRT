#include "../miniRT.h"

t_Plane		*rt_last_Plane(t_Plane *Plane)
{
	t_Plane     *p_lst;

	p_lst = Plane;
	if (p_lst)
	{
		while (p_lst->next)
			p_lst = p_lst->next;
	}
	return (p_lst);
}

t_Sphere	*rt_last_Sphere(t_Sphere *Sphere)
{
	t_Sphere     *s_lst;

	s_lst = Sphere;
	if (s_lst)
	{
		while (s_lst->next)
			s_lst = s_lst->next;
	}
	return (s_lst);
}

t_Cylinder	*rt_last_Cylinder(t_Cylinder *Cylinder)
{
	t_Cylinder     *c_lst;

	c_lst = Cylinder;
	if (c_lst)
	{
		while (c_lst->next)
			c_lst = c_lst->next;
	}
	return (c_lst);
}
