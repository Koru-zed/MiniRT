#pragma once
#include "miniRT.h"
#include <float.h>
/********* struct for test ********/


/*
 *  we could represent the color by percentage
 *  between 0.0 to 1.0
 * */
/*
typedef struct s_color {
	double red, green, blue;
} colour;


typedef struct s_material{
	colour diffuse;
	double	reflection;
}	t_material;

typedef struct	s_light {
	t_point	pos;
	colour 	intensity;
}	t_light;


typedef struct	s_sphere {
	t_point	pos;
	double	radius;
	int		material;
}	t_sphere;
*/

/********************/
typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		width;
	int		height;
    int		bits_per_pixel;
    int		line_length;
	int		endian;
    int     obj;
    int     rotate;
    // int     dir;
    int     _do;
}			t_mlx;

typedef struct _num_shape
{
    int     A;
    int     C;
    int     L;
    int     pl;
    int     sp;
    int     cy;
} t_num_shape;

typedef struct _data {

    char    *info;//change
    char    **pars;
    int     check_empty;
    t_num_shape shape;
    struct  _data *next;
}   t_data;

typedef struct	point {

	double	x;
	double	y;
	double	z;
}	t_point;


typedef struct	s_color {

	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_material {
	t_color	objColor;
	t_color eff_color;
	t_color diffuse_color;
	t_color ambColor;
	t_color	rgb;
}	t_rgbMaterial;

typedef struct s_p_intersect {
	t_point hit_pos;
	t_point normal;
	double	hit_mag;
	t_color	obj_color;
} t_hit;
    // t_point left_corner;
    // t_point horizontal;
    // t_point vertical;
typedef struct	s_ray {

    t_point origin;
    t_point direction;
    double   t;
}	t_ray;

typedef struct matrix
{
	double	M[4][4];
}				t_matrix;

typedef struct _Ambient_light
{
    double   ratio;//ambient lighting ratio in range [0.0,1.0]:
    size_t  color[3];//R,G,B colors in range [0-255]: 255, 255, 255
    size_t  repetition;
} t_Ambient;

typedef struct _Camera
{
    int fd;
    size_t    fov;// ->
    size_t    repetition;
    t_ray	  ray;
    t_matrix  matrix;
} t_Camera;
typedef struct delta {
	double a;
	double b;
	double c;
	double delta;
} t_delta;
typedef struct _Light
{
    t_point   cordinates;//x,y,z coordinates of the view
    double    brightenss;//the light brightness ratio in range [0.0,1.0]
    size_t   color[3];//R,G,B colors in range [0-255]: 255, 255, 255
    size_t   repetition;
} t_Light;

typedef struct s_intersect {
	double	tmin;
	t_point	closestPoint;
	size_t	*color;
} t_intersect;

typedef struct _Plane
{
    // t_point         plane_point;//x,y,z coordinates of the view
    // t_point         normal;//3d normalized orientation vector. In range [-1,1]
    t_ray	        ray;
    size_t          color[3];//R,G,B colors in range [0-255]: 255, 255, 255
    size_t          repetition;
	t_point			local_hit_point; // store the hit point
    t_matrix  matrix;
    // struct _Plane   *next;
} t_Plane;

typedef struct _Sphere
{
	t_point         center;//x,y,z coordinates of the view
	double			radius;
	size_t			color[3];//R,G,B colors in range [0-255]: 255, 255, 255
	size_t			repetition;

    // struct _Sphere   *next;
} t_Sphere;

typedef struct _Cylinder
{
    t_point             cordinates;//x,y,z coordinates of the view
    t_point             orientation;//3d normalized orientation vector. In range [-1,1]
    size_t              color[3];//R,G,B colors in range [0-255]: 255, 255, 255
    double               redius;
    double               height;
	double				cyMin;
	double				cyMax;
    size_t              repetition;
    // struct _Cylinder    *next;
} t_Cylinder;

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
