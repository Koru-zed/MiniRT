#ifndef  MINIRT_H  
# define MINIRT_H 

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include "../get_next_line/get_next_line.h"
# include "structs.h"

# define ambient "A"
# define camera "C"
# define light "L"
# define plane "pl"
# define sphre "sp"
# define cylinder "cy"



void        free_mini(t_minirt *mini);
void        free_data(t_data *_data);
void        free_Cylinder(t_Cylinder *_Cylinder);
void        free_Plane(t_Plane *_Plane);
void        free_Sphere(t_Sphere *_Sphere);
void	my_mlx_pixel_put(t_mlx *Mlx, int x, int y, int color);
t_Cylinder	*rt_last_Cylinder(t_Cylinder *Cylinder);
t_Sphere	*rt_last_Sphere(t_Sphere *Sphere);
t_Plane	    *rt_last_Plane(t_Plane *Plane);

void        set_color(char const *colors, size_t *table, t_minirt *mini);
void        set_orientation(char const *colors, float *table, t_minirt *mini);
void        set_cordinates(char const *cord, float *table, t_minirt *mini);

int         get_Light(t_minirt *mini, t_data *data);
int         get_Camera(t_minirt *mini, t_data *data);
int         get_Ambient_lightning(t_minirt *mini, t_data *data);
int         get_Plane(t_minirt *mini, t_data *data);
int         get_Sphere(t_minirt *mini, t_data *data);
int         get_Cylinder(t_minirt *mini, t_data *data);

void        fill_data(t_data *n_data, int fd);
int         ft_check_valid(char *filename, t_data *data);

size_t      check_data(t_minirt *mini, t_data *data);
void        fill_Info(t_minirt *mini);

void	draw_line(t_mlx *info, int color);

#endif