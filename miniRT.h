#ifndef  MINIRT_H  
# define MINIRT_H 

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include "get_next_line/get_next_line.h"

# define ambient "A"
# define camera "C"
# define light "L"
# define plane "pl"
# define sphre "sp"
# define cylinder "cy"


typedef struct _data {

    struct _data *prev;
    char    *array;
    int     check_empty;
    struct _data *next;

}   t_data;

typedef struct _Ambient_light
{
    float   ratio;//ambient lighting ratio in range [0.0,1.0]:
    size_t  color[3];//R,G,B colors in range [0-255]: 255, 255, 255
    size_t    repetition;
} t_Ambient;

typedef struct _Camera
{
    float   cordinates[3];//x,y,z coordinates of the view
    float   orientation[3];//3d normalized orientation vector. In range [-1,1] 
    size_t  fov;//Horizontal field of view in degrees in range [0,180]
    size_t    repetition;
} t_Camera;

typedef struct _Light
{
    float   cordinates[3];//x,y,z coordinates of the view
    float   brightenss;//the light brightness ratio in range [0.0,1.0]
    size_t  color[3];//R,G,B colors in range [0-255]: 255, 255, 255
    size_t    repetition;
} t_Light;

typedef struct _Sphere
{
    float   cordinates[3];//x,y,z coordinates of the view
    float   diameter;
    size_t  color[3];//R,G,B colors in range [0-255]: 255, 255, 255
} t_Sphere;

typedef struct _Plane
{
    float   cordinates[3];//x,y,z coordinates of the view
    float   orientation[3];//3d normalized orientation vector. In range [-1,1] 
    size_t  color[3];//R,G,B colors in range [0-255]: 255, 255, 255
} t_Plane;

typedef struct _Cylinder
{
    float   cordinates[3];//x,y,z coordinates of the view
    float   orientation[3];//3d normalized orientation vector. In range [-1,1]
    size_t  color[3];//R,G,B colors in range [0-255]: 255, 255, 255
    float   diameter;
    float   hright;
} t_Cylinder;

typedef struct _minirt {

    int         fd;
    size_t        check;
    char        *file;
    t_Ambient   *Ambient;
    t_Camera    *Camera;
    t_Light     *Light;
    t_Sphere    *Sphere;
    t_Plane     *Plane;
    t_Cylinder  *Cylinder;
    t_data      *data;

}   t_minirt;

#endif