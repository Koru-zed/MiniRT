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
#include <stdbool.h>

# define ambient "A"
# define camera "C"
# define light "L"
# define plane "pl"
# define sphre "sp"
# define cylinder "cy"



void		free_mini(t_minirt *mini);
void		free_data(t_data *_data);
void		free_Cylinder(t_Cylinder *_Cylinder);
void		free_Plane(t_Plane *_Plane);
void		free_Sphere(t_Sphere *_Sphere);
void		my_mlx_pixel_put(t_mlx *Mlx, int x, int y, int color);
t_Cylinder	*rt_last_Cylinder(t_Cylinder *Cylinder);
t_Sphere	*rt_last_Sphere(t_Sphere *Sphere);
t_Plane		*rt_last_Plane(t_Plane *Plane);

void		set_color(char const *colors, size_t *table, t_minirt *mini);
void		set_orientation(char const *colors, float *table, t_minirt *mini);
void		set_cordinates(char const *cord, float *table, t_minirt *mini);

int			get_Light(t_minirt *mini, t_data *data);
int			get_Camera(t_minirt *mini, t_data *data);
int			get_Ambient_lightning(t_minirt *mini, t_data *data);
int			get_Plane(t_minirt *mini, t_data *data);
int			get_Sphere(t_minirt *mini, t_data *data);
int			get_Cylinder(t_minirt *mini, t_data *data);

void        fill_data(t_data *n_data, int fd);
int         ft_check_valid(char *filename, t_data *data);

size_t      check_data(t_minirt *mini, t_data *data);
void        fill_Info(t_minirt *mini);
void		draw_line(t_mlx *info, int color);
void 		ray_render(t_minirt *minirt);

/* ***		Math Operations		** */
float		dot(const t_point u, const t_point v);
t_point		cross(const t_point u, const t_point v);
t_point		mul(const float t,  t_point p);
t_point		division(t_point p, float t);
t_point		adding(t_point p, t_point v);
t_point		sub(t_point center, t_point origin);
unsigned long	createRGB(double r, double g, double b);
float		 	length_squared(t_point p);
float			length(t_point p);
t_point			unit_vector(t_point v);
/* ***		End Math Operations		** */
bool 	intersectRaySphere(t_ray *r, t_Sphere *s, float *t);
//bool	intersectRaySphere(t_ray *r, t_sphere *s, float *t);


#endif