/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-jao <mait-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 10:43:03 by ael-mous          #+#    #+#             */
/*   Updated: 2022/12/08 13:09:07 by mait-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  MINIRT_H
# define MINIRT_H

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include "../get_next_line/get_next_line.h"
# include "structs.h"
# include <sys/time.h>
# include <stdbool.h>

# define AMBIENT "A"
# define CAMERA "C"
# define LIGHT "L"
# define PLANE "pl"
# define SEPHER "sp"
# define CYLINDER "cy"
# define HEIGHT 720
# define WIDTH 1080
# define EPSILON 1.0e-4f
# define BLACK 0x000000
# define KEYDOWN  125
# define KEYUP  126
# define KEYLEFT  123
# define KEYRIGHT  124
# define _SEPHER 1
# define _PLANE 35
# define _LIGHT 37
# define _CYLINDER 8
# define _CAMERA 9
# define MOUSEDOWN  4
# define MOUSEUP  5
# define ROTATE_X 7
# define ROTATE_Y 16
# define ROTATE_Z 6
# define ZERO 29
# define R_LEFT 43
# define R_RIGHT 47
# define PL 0
# define SP 1
# define CY 2
# define DESTROY 53
# define CLOSE 17

t_color		add_2colors(t_color obj, t_color obj2);
void		mix_color(t_minirt *rt, t_hit *pHit, t_rgbMaterial *rgbMat);
int			check(int r);
int			free_mini(t_minirt *mini);
void		free_data(t_data *_data);
void		my_mlx_pixel_put(t_mlx *Mlx, int x, int y, int color);
void		set_color(char const *colors, size_t *table, t_minirt *mini);
void		set_orientation(char const *colors, t_point *cord, t_minirt *mini);
void		set_cordinates(char const *cord, t_point *cordinate, t_minirt *rt);
t_color		add_color(const size_t *c);
int			get_light(t_minirt *mini, t_data *data);
int			get_camera(t_minirt *mini, t_data *data);
int			get_ambient_lightning(t_minirt *mini, t_data *data);
int			get_plane(t_minirt *mini, t_data *data);
int			get_sphere(t_minirt *mini, t_data *data);
int			get_cylinder(t_minirt *mini, t_data *data);

void		fill_data(t_data *n_data, t_num_shape *n_shape, int fd);
int			ft_check_valid(char *filename, t_data *data, t_num_shape *_shape);

size_t		check_data(t_minirt *mini, t_data *data);
void		fill_info(t_minirt *mini);
void		ray_render(t_minirt *minirt);
t_color		creat_color(size_t r, size_t g, size_t b);
t_point		new_point(double x, double y, double z);

/* ***		Math Operations		** */
double		v_dot(const t_point u, const t_point v);
t_point		v_cross(const t_point u, const t_point v);
t_point		v_mul(const double t, t_point p);
t_point		v_division(t_point p, double t);
t_point		v_adding(t_point p, t_point v);
t_point		v_sub(t_point center, t_point origin);

double		length_squared(t_point p);
t_point		normalizing(t_point p);
int			rgb(t_color rgb);

/* ***		End Math Operations		** */
void		ft_print_vector(const t_point p);
t_color		mul_color(t_color color, double s);
/*
	! ~ intersection test functions.
 */
void		iterate_over_objects(t_minirt *rt, t_ray r, double *t, t_hit **Hit);
bool		add_light(t_hit *pHit, t_minirt *rt, int *c);
t_ray		ray_generator(t_minirt *mini, int x, int y);
bool		intersect_r_sphere(t_ray r, t_minirt *s, double *t, t_hit *pHit);
bool		intersect_plane(t_minirt *rt, t_ray ray, double *t, t_hit *pHit);
t_matrix	dir_matrix(void);
void		camera_matrix(t_Camera *_camera);
void		fill_plane_matrix(t_Plane *_plane);
t_matrix	new_matrix(t_point u, t_point v, t_point w, t_point T);
t_matrix	update_matrix_x(double theta);
t_matrix	update_matrix_y(double theta);
t_matrix	update_matrix_z(double theta);
t_point		mul_point_matrix(t_point p, t_matrix m);
t_point		at(double t, t_ray *r);
t_matrix	cross_matrix(t_matrix M1, t_matrix M2);
void		print_matrix(t_matrix matrix);
void		rotation_plane(t_minirt *mini, int e);

void		rotation_cylinder(t_minirt *mini, int key);
void		intersection_over_objects(t_minirt *rt, t_ray ray);
bool		cylinder_intersection(t_minirt *rt, t_ray r, double *t, t_hit *hit);

#endif
