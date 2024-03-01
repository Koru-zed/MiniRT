/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-jao <mait-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:04:34 by mait-jao          #+#    #+#             */
/*   Updated: 2022/12/08 21:20:39 by mait-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "miniRT.h"
# include <float.h>

typedef struct _select
{
	int	index;
	int	object;
}	t_select;

typedef struct s_mlx
{
	void		*_mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			width;
	int			height;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			rotate;
	int			mouse;
	int			_do;
	t_select	obj;
}	t_mlx;

typedef struct s_quadratic
{
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	sqrt_disc;
}	t_quadratic;

typedef struct num_shape
{
	int	a;
	int	c;
	int	l;
	int	pl;
	int	sp;
	int	cy;
}	t_num_shape;

typedef struct data
{
	char		*info;
	char		**pars;
	int			check_empty;
	t_num_shape	shape;
	struct data	*next;
}	t_data;

typedef struct point
{
	double	x;
	double	y;
	double	z;
}	t_point;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_material
{
	t_color	eff_color;
	t_color	diffuse_color;
}	t_rgbMaterial;

typedef struct s_p_intersect
{
	t_point	hit_pos;
	t_point	normal;
	double	hdest;
	t_color	obj_color;
}	t_hit;

typedef struct s_ray
{
	t_point	origin;
	t_point	direction;
}	t_ray;

typedef struct matrix
{
	double	m[4][4];
}	t_matrix;

typedef struct Ambient_light
{
	double	ratio;
	size_t	color[3];
	size_t	repetition;
}	t_Ambient;

typedef struct Camera
{
	int			fd;
	size_t		fov;
	size_t		repetition;
	t_ray		ray;
	t_matrix	matrix;
}	t_View;

typedef struct Light
{
	t_point	cordinates;
	double	brightenss;
	size_t	color[3];
	size_t	repetition;
}	t_Light;

typedef struct s_intersect
{
	double	tmin;
	t_point	closestpoint;
	size_t	*color;

}	t_intersect;

typedef struct Plane
{
	t_ray		ray;
	size_t		color[3];
	size_t		repetition;
	t_point		local_hit_point;
	t_matrix	matrix;
}	t_Plane;

typedef struct Sphere
{
	t_point	center;
	double	radius;
	size_t	color[3];
	size_t	repetition;
}	t_Sphere;

typedef struct Cylinder
{
	t_point		x;
	t_quadratic	q;
	t_point		top;
	t_point		h_hat;
	t_ray		ray;
	double		redius;
	double		height;
	size_t		color[3];
	size_t		repetition;
}	t_Cylinder;

typedef struct minirt
{
	int			fd;
	int			check;
	char		*file;
	t_Ambient	*ambient;
	t_View	*camera;
	t_Light		*light;
	t_Sphere	*sphere;
	t_Plane		*plane;
	t_Cylinder	*cylinder;
	t_data		*data;
	t_mlx		*mlx;
}	t_minirt;

#endif