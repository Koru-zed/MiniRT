#pragma once
#include "miniRT.h"

typedef struct _data {

    char    *info;//change
    char    **pars;
    int     check_empty;
    struct _data *next;

}   t_data;

typedef struct _Ambient_light
{
    float   ratio;//ambient lighting ratio in range [0.0,1.0]:
    size_t  color[3];//R,G,B colors in range [0-255]: 255, 255, 255
    size_t  repetition;
} t_Ambient;

typedef struct _Camera
{
    float   cordinates[3];//x,y,z coordinates of the view
    float   orientation[3];//3d normalized orientation vector. In range [-1,1] 
    size_t  fov;//Horizontal field of view in degrees in range [0,180]
    size_t  repetition;
} t_Camera;

typedef struct _Light
{
    float   cordinates[3];//x,y,z coordinates of the view
    float   brightenss;//the light brightness ratio in range [0.0,1.0]
    size_t  color[3];//R,G,B colors in range [0-255]: 255, 255, 255
    size_t   repetition;
} t_Light;

typedef struct _Plane
{
    float           cordinates[3];//x,y,z coordinates of the view
    float           orientation[3];//3d normalized orientation vector. In range [-1,1] 
    size_t          color[3];//R,G,B colors in range [0-255]: 255, 255, 255
    size_t          repetition;
    struct _Plane   *next;
} t_Plane;

typedef struct _Sphere
{
    float           cordinates[3];//x,y,z coordinates of the view
    float           diameter;
    size_t          color[3];//R,G,B colors in range [0-255]: 255, 255, 255
    size_t          repetition;
    struct _Sphere   *next;
} t_Sphere;

typedef struct _Cylinder
{
    float               cordinates[3];//x,y,z coordinates of the view
    float               orientation[3];//3d normalized orientation vector. In range [-1,1]
    size_t              color[3];//R,G,B colors in range [0-255]: 255, 255, 255
    float               diameter;
    float               hright;
    size_t              repetition;
    struct _Cylinder    *next;
} t_Cylinder;

typedef struct _mlx {

void    *img;
void    *mlx;
void    *win;
char	*addr;
int		bits_per_pixel;
int		line_length;
int		endian;
int     x[2];
int     y[2];
int     z[2];
int     d[2];
int     s[2];

} t_mlx;


typedef struct _minirt {

    int         fd;
    int         check;
    char        *file;
    t_Ambient   *Ambient;
    t_Camera    *Camera;
    t_Light     *Light;
    t_Sphere    *Sphere;
    t_Plane     *Plane;
    t_Cylinder  *Cylinder;
    t_data      *Data;
    t_mlx       *Mlx;
}   t_minirt;
