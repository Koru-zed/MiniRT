#include "Include/miniRT.h"


long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

// t_point	ray_pixel_to_world(t_minirt *mini, int x, int y)
// {
// 	float	aspect_ratio;
// 	float	half_hight;
// 	float   half_width;
// 	float	p_x;
// 	float	p_y;

// 	half_hight = tanf((float )((float )mini->Camera->fov * M_PI / 180) / 2);
// 	aspect_ratio = (float )mini->Mlx->width / (float )mini->Mlx->height;
// 	half_width = half_hight * aspect_ratio;
// 	p_x = (float )(2 * (x + 0.5) / mini->Mlx->width - 1) * half_width;
// 	p_y = (float )(1 - 2 * (y + 0.5) / mini->Mlx->height) * half_hight;
// 	return (new_point(-p_x, p_y, 1));
// }

t_point	ray_pixel_to_world(t_minirt *mini, int x, int y)
{
	float	aspect_ratio;
	float	half_hight;
	float   half_width;
	float	ps_x;
	float	ps_y;

	// half_hight = tanf((float )mini->Camera->fov / 2.0f);
	half_hight = tanf((float )((float )mini->Camera->fov * M_PI / 180) / 2);
	aspect_ratio = (float)mini->Mlx->width / (float)mini->Mlx->height;
	half_width = half_hight * aspect_ratio;
	ps_x = (float )(2 * (x + 0.5) / mini->Mlx->width - 1) * half_width;
	ps_y = (float )(1 - 2 * (y + 0.5) / mini->Mlx->height) * half_hight;
	return (new_point(ps_x, ps_y, 1));
}

t_ray	ray_generator(t_minirt *mini, int x, int y)
{
	t_point	shooting_direction;
	t_ray	ray;

	shooting_direction = ray_pixel_to_world(mini, x, y);
	shooting_direction = mul_point_matrix(shooting_direction, mini->Camera->matrix);
	shooting_direction = v_sub(shooting_direction, mini->Camera->ray.origin);
	shooting_direction = normalizing(shooting_direction);
	ray.origin = mini->Camera->ray.origin;
	ray.direction = shooting_direction;
	return (ray);
}

// +

void edit_camera(t_minirt *mini, int key)
{
	// printf("Camera\n");
	mini->Mlx->_do = 1; 
	if (key == KEYUP)
		mini->Camera->ray.origin.y -= 0.125;
	else if (key == KEYDOWN)
		mini->Camera->ray.origin.y += 0.125;
	else if (key == KEYLEFT)
		mini->Camera->ray.origin.x += 0.125;
	else if (key == KEYRIGHT)
		mini->Camera->ray.origin.x -= 0.125;
	else if (key == KEY_A)////////////////////////////
		mini->Camera->ray.origin = mul_point_matrix(mini->Camera->ray.origin, mini->Camera->matrix);
	else if (key == R_RIGHT)
		mini->Camera->ray.origin = mul_point_matrix(mini->Camera->ray.origin, mini->Camera->matrix);
	else
		mini->Mlx->_do = 0; 
}

// void edit_light(t_minirt *mini, int key)
// {

// }

void edit_sepher(t_minirt *mini, int key)
{
	int i;
	// printf("Sepher\n");
	// mini->Mlx->_do = 1; 
	// if (key == KEYUP)
	// 	mini->Sphere->center.y += 0.5;
	// else if (key == KEYDOWN)
	// 	mini->Sphere->center.y -= 0.5;
	// else if (key == KEYLEFT)
	// 	mini->Sphere->center.x -= 0.5;
	// else if (key == KEYRIGHT)
	// 	mini->Sphere->center.x += 0.5;
	// else
	// 	mini->Mlx->_do = 0; 
	// printf("hello\n");
	mini->Mlx->_do = 1;
	if (key == KEYUP){
		i = -1;
		while (++i < mini->Data->shape.sp)
			mini->Sphere[i].center.y += 0.75;
	}
	else if (key == KEYDOWN){
		i = -1;
		while (++i < mini->Data->shape.sp)
			mini->Sphere[i].center.y -= 0.75;
	}
	else if (key == KEYLEFT){
		i = -1;
		while (++i < mini->Data->shape.sp)
			mini->Sphere[i].center.x += 0.75;
	}
	else if (key == KEYRIGHT)
	{
		i = -1;
		while (++i < mini->Data->shape.sp)
			mini->Sphere[i].center.x -= 0.75;
	}
	else
		mini->Mlx->_do = 0; 

}

int rotation_key(int key, t_minirt *mini)
{
	// t_matrix M;÷
	// static int theta;
	// static int e;

	
	if (key == ROTATE_X)
		mini->Mlx->rotate = ROTATE_X;
	else if (key == ROTATE_Y)
		mini->Mlx->rotate = ROTATE_Y;
	else if (key == ROTATE_Z)
		mini->Mlx->rotate = ROTATE_Z;
	// if (key == R_RIGHT){
	// 	// printf("hala\n");
	// 	// if (theta < 360)
	// 	// 	theta += 30;
	// 	// else 
	// 	// 	theta = 0;
	// 	// // update_matrix_x(theta);
	// 	// mini->Camera->matrix = cross_matrix(update_matrix_x(theta), mini->Camera->matrix);
	// 	// print_matrix(mini->Camera);
	// 	rotation_plane(mini, 1);
	// 	// printf("plane_dir->x{%f} | plane_dir->y{%f} | plane_dir->z{%f}\n", mini->Plane->normal.x, mini->Plane->normal.y, mini->Plane->normal.z);
	// 	// else if (mini->Mlx->rotate == ROTATE_X && mini->Plane->normal.x >= -1)
	// 	// 	mini->Plane->normal.x += ;
	// 	// else if (mini->Mlx->rotate == ROTATE_Y && mini->Plane->normal.y >= -1)
	// 	// 	mini->Plane->normal.y += ;
	// 	// else if (mini->Mlx->rotate == ROTATE_Z && mini->Plane->normal.z >= -1)
	// 	// 	mini->Plane->normal.z += ;
	// }
	// else if (key == R_LEFT){
	// 	// printf("hala\n");
	// 	// if (theta < 360)
	// 	// 	theta += 30;
	// 	// else 
	// 	// 	theta = 0;
	// 	// // update_matrix_y(theta);
	// 	// mini->Camera->matrix = cross_matrix(update_matrix_y(theta), mini->Camera->matrix);
	// 	// print_matrix(mini->Camera);
	// 	// if (mini->Mlx->rotate == ROTATE_X && mini->Plane->normal.x <= 1)
	// 	// 	mini->Plane->normal.x += ;
	// 	// else if (mini->Mlx->rotate == ROTATE_Y && mini->Plane->normal.y <= 1)
	// 	// 	mini->Plane->normal.y += ;
	// 	// else if (mini->Mlx->rotate == ROTATE_Z && mini->Plane->normal.z <= 1)
	// 	// 	mini->Plane->normal.z += ;
	// 	// else if (mini->Mlx->rotate == ROTATE_X && mini->Plane->normal.x >= -1)
	// 	// 	mini->Plane->normal.x += ;
	// 	// else if (mini->Mlx->rotate == ROTATE_Y && mini->Plane->normal.y >= -1)
	// 	// 	mini->Plane->normal.y += ;
	// 	// else if (mini->Mlx->rotate == ROTATE_Z && mini->Plane->normal.z >= -1)
	// 	// 	mini->Plane->normal.z += ;
	// 	rotation_plane(mini, -1);
	// 	// printf("plane_dir->x{%f} | plane_dir->y{%f} | plane_dir->z{%f}\n", mini->Plane->normal.x, mini->Plane->normal.y, mini->Plane->normal.z);
	// }
	// else if (key == R_RIGHT){
	// 	// printf("hala\n");
	// 	// if (theta < 360)
	// 	// 	theta += 30;
	// 	// else 
	// 	// 	theta = 0;
	// 	// // update_matrix_z(theta);
	// 	// mini->Camera->matrix = cross_matrix(update_matrix_x(theta), mini->Camera->matrix);
	// 	// print_matrix(mini->Camera);
	// }
	// else if (key == KEY_A){
	// 	// printf("hala\n");
	// 	// if (theta > 0)
	// 	// 	theta -= 30;
	// 	// else 
	// 	// 	theta = 360;
	// 	// // update_matrix_x(theta);
	// 	// mini->Camera->matrix = cross_matrix(update_matrix_x(theta), mini->Camera->matrix);
	// 	// print_matrix(mini->Camera);
	// }
	// else if (key == KEY_A && mini->Mlx->rotate == ROTATE_Y){
	// 	// printf("hala\n");
	// 	// if (theta > 0)
	// 	// 	theta -= 30;
	// 	// else 
	// 	// 	theta = 360;
	// 	// // update_matrix_y(theta);
	// 	// mini->Camera->matrix = cross_matrix(update_matrix_x(theta), mini->Camera->matrix);
	// 	// print_matrix(mini->Camera);
	// }
	// else if (key == KEY_A && mini->Mlx->rotate == ROTATE_Z){
	// 	// printf("hala\n");
	// 	// if (theta > 0)
	// 	// 	theta -= 30;
	// 	// else 
	// 	// 	theta = 360;
	// 	// // update_matrix_z(theta);
	// 	// mini->Camera->matrix = cross_matrix(update_matrix_x(theta), mini->Camera->matrix);
	// 	// print_matrix(mini->Camera);
	// }
	return (0);
}

void edit_plane(t_minirt *mini, int key)
{
	int i;
	// t_Plane *head;
		// printf("Plane\n");
	mini->Mlx->_do = 1;
	if (key == KEYUP){
		i = -1;
		while (++i < mini->Data->shape.pl)
			mini->Plane[i].plane_point.y += 0.75;
	}
	else if (key == KEYDOWN){
		i = -1;
		while (++i < mini->Data->shape.pl)
			mini->Plane[i].plane_point.y -= 0.75;
	}
	else if (key == KEYLEFT){
		i = -1;
		while (++i < mini->Data->shape.pl)
			mini->Plane[i].plane_point.x += 0.75;
	}
	else if (key == KEYRIGHT)
	{
		i = -1;
		while (++i < mini->Data->shape.pl)
			mini->Plane[i].plane_point.x -= 0.75;
	}
	else if (key == R_RIGHT)
		rotation_plane(mini, -1);
	else if (key == R_LEFT)
		rotation_plane(mini, 1);
	// else if (key == KEY_A)
	// {
	// 	// i = -1;
	// 	// while (++i < mini->Data->shape.pl)
	// 	mini->Plane[0].plane_point = mul_point_matrix(mini->Plane[0].plane_point, mini->Camera->matrix);
	// }
	// else if (key == R_RIGHT)
	// {
	// 	// i = -1;
	// 	// while (++i < mini->Data->shape.pl)
	// 	mini->Plane[0].plane_point = mul_point_matrix(mini->Plane[0].plane_point, mini->Camera->matrix);
	// }
	else
		mini->Mlx->_do = 0; 
}

// void edit_cylinder(t_minirt *mini, int key)
// {

// }

void edit_mini(t_minirt *mini, int key)
{
	if (mini->Mlx->obj == _CAMERA)
		edit_camera(mini, key);
	// else if (key == _LIGHT)
	// 	edit_light(mini, key);
	else if (mini->Mlx->obj == _SEPHER)
		edit_sepher(mini, key);
	else if (mini->Mlx->obj == _PLANE)
		edit_plane(mini, key);
	// else if (key == _CYLINDER)
	// 	edit_cylinder(mini, key);
	// mini->Mlx->addr = mlx_get_data_addr(mini->Mlx->img, &mini->Mlx->bits_per_pixel, &mini->Mlx->line_length, &mini->Mlx->endian);
	if (mini->Mlx->_do)
	{
		mlx_clear_window(mini->Mlx->mlx, mini->Mlx->win);
		ray_render(mini);
	}
}

// void edit_mini(t_minirt *mini, int key)
// {
// 	if 
// }
int objs_key(int key, t_minirt *mini)
{
	if (key == _CAMERA)
		mini->Mlx->obj = _CAMERA;
	else if (key == _LIGHT)
		mini->Mlx->obj = _LIGHT;
	else if (key == _SEPHER)
		mini->Mlx->obj = _SEPHER;
	else if (key == _PLANE)
		mini->Mlx->obj = _PLANE;
	else if (key == _CYLINDER)
		mini->Mlx->obj = _CYLINDER;
	// else
	// 	mini->Mlx->obj = -1;
	// printf("key_objs{%d}{%d}\n", key, mini->Mlx->obj);
	return (0);
}

t_matrix update_matrix_x(int theta)
{
	t_matrix matrix;

	matrix.M[0][0] = 1;
	matrix.M[0][1] = 0;
	matrix.M[0][2] = 0;
	matrix.M[0][3] = 0;
	matrix.M[1][0] = 0;
	matrix.M[1][1] = (float )cos(theta);
	matrix.M[1][2] = -(float )sin(theta);
	matrix.M[1][3] = 0;
	matrix.M[2][0] = 0;
	matrix.M[2][1] = (float )sin(theta);
	matrix.M[2][2] = (float )cos(theta);
	matrix.M[2][3] = 0;
	matrix.M[3][1] = 0;
	matrix.M[3][2] = 0;
	matrix.M[3][1] = 0;
	matrix.M[3][2] = 1;
	return (matrix);
}

t_matrix update_matrix_y(int theta)
{
	t_matrix matrix;

	matrix.M[0][0] = (float )cos(theta);
	matrix.M[0][1] = 0;
	matrix.M[0][2] = (float )sin(theta);
	matrix.M[0][3] = 0;
	matrix.M[1][0] = 0;
	matrix.M[1][1] = 1;
	matrix.M[1][2] = 0;
	matrix.M[1][3] = 0;
	matrix.M[2][0] = -(float )sin(theta);
	matrix.M[2][1] = 0;
	matrix.M[2][2] = (float )cos(theta);
	matrix.M[2][3] = 0;
	matrix.M[3][1] = 0;
	matrix.M[3][2] = 0;
	matrix.M[3][1] = 0;
	matrix.M[3][2] = 1;
	return (matrix);
}

t_matrix update_matrix_z(int theta)
{
	t_matrix matrix;

	matrix.M[0][0] = (float )cos(theta);
	matrix.M[0][1] = -(float )sin(theta);
	matrix.M[0][2] = 0;
	matrix.M[0][3] = 0;
	matrix.M[1][0] = (float)sin(theta);
	matrix.M[1][1] = (float)cos(theta);
	matrix.M[1][2] = 0;
	matrix.M[1][3] = 0;
	matrix.M[2][0] = 0;
	matrix.M[2][1] = 0;
	matrix.M[2][2] = 1;
	matrix.M[2][3] = 0;
	matrix.M[3][1] = 0;
	matrix.M[3][2] = 0;
	matrix.M[3][1] = 0;
	matrix.M[3][2] = 1;
	return (matrix);
}

void	rotation_plane(t_minirt *mini, int e)
{
	static float cycle;

	// if (mini->Plane->normal.x == 1)
	// 	cycle.x = -0.1;
	// else if (mini->Plane->normal.y == 1)
	// 	cycle.y = -0.1;
	// else if (mini->Plane->normal.z == 1)
	// 	cycle.z = -0.1;
    // else if (mini->Plane->normal.x <= 1)
	// 	cycle.x = 0.1;
	// else if (mini->Plane->normal.y <= 1)
	// 	cycle.y = 0.1;
	// else if (mini->Plane->normal.z <= 1)
	// 	cycle.z = 0.1;
	// if (mini->)
		// cycle = 0.1f;
	mini->Mlx->_do = 1;
	if (mini->Mlx->rotate == ROTATE_X && (mini->Plane->normal.x <= 1 && mini->Plane->normal.x >= -1))
	{
		if (mini->Plane->normal.x == 1)
			cycle = -1 * e;
		else
			cycle = 1 * e;
		mini->Plane->normal.x += 0.1f * cycle;
	}
	else if (mini->Mlx->rotate == ROTATE_Y && (mini->Plane->normal.y <= 1 && mini->Plane->normal.x >= -1))
	{
		if (mini->Plane->normal.y == 1)
			cycle = -1 * e;
		else
			cycle = 1 * e;
		mini->Plane->normal.y += 0.1f * cycle;
	}
	else if (mini->Mlx->rotate == ROTATE_Z && (mini->Plane->normal.z <= 1 && mini->Plane->normal.x >= -1))
	{
		if (mini->Plane->normal.z == 1)
			cycle = -1 * e;
		else
			cycle = 1 * e;
		mini->Plane->normal.z += 0.1f * cycle;
	}
	printf("cycle {%f}\n", cycle);
	printf("Plane->normal.x = %f, Plane->normal.y = %f, Plane->normal.z = %f\n", mini->Plane->normal.x, mini->Plane->normal.y, mini->Plane->normal.z);
}


int press_key(int key, t_minirt *mini)
{
	if (key == KEYUP)
		edit_mini(mini, key);
	else if (key == KEYDOWN)
		edit_mini(mini, key);
	else if (key == KEYLEFT)
		edit_mini(mini, key);
	else if (key == KEYRIGHT)
		edit_mini(mini, key);
	else if (key == DESTROY)
		edit_mini(mini, key);
	else if (key == R_RIGHT)
		edit_mini(mini, key);
	else if (key == R_LEFT)
		edit_mini(mini, key);
	else if (key == ZERO)
	{
		mini->Mlx->obj = 0;
		mini->Mlx->rotate = 0;
		mini->Mlx->_do = -1;
	}
	objs_key(key, mini);
	rotation_key(key, mini);
	printf("key_press{%d} | rotate {%d} | shape{%d}\n", key, mini->Mlx->rotate, mini->Mlx->obj);
	return (0);
}


// +
void	setup_controls(t_minirt *mini)
{
	// mlx_hook(mini->Mlx->win, 4, 0, ft_mouse, mini);
	// mlx_hook(mini->Mlx->win, 5, 0, ft_mouse, mini);
	// mlx_key_hook(mini->Mlx->win, objs, mini);
	mlx_key_hook(mini->Mlx->win, press_key, mini);
}

void print_matrix(t_Camera *_camera)
{
	printf("fd{%d}\n", _camera->fd);
	ft_putstr_fd("########\n", _camera->fd);
	ft_putstr_fd("M[0][0] = ", _camera->fd);
	ft_putnbr_fd(_camera->matrix.M[0][0], _camera->fd);
	ft_putstr_fd(" | M[0][1] = ", _camera->fd);
	ft_putnbr_fd(_camera->matrix.M[0][1], _camera->fd);
	ft_putstr_fd(" | M[0][2] = ", _camera->fd);
	ft_putnbr_fd(_camera->matrix.M[0][2], _camera->fd);
	ft_putstr_fd(" | M[0][3] = ", _camera->fd);
	ft_putnbr_fd(_camera->matrix.M[0][3], _camera->fd);
	ft_putchar_fd('\n', _camera->fd);
	ft_putstr_fd("M[1][0] = ", _camera->fd);
	ft_putnbr_fd(_camera->matrix.M[1][0], _camera->fd);
	ft_putstr_fd(" | M[1][1] = ", _camera->fd);
	ft_putnbr_fd(_camera->matrix.M[1][1], _camera->fd);
	ft_putstr_fd(" | M[1][2] = ", _camera->fd);
	ft_putnbr_fd(_camera->matrix.M[1][2], _camera->fd);
	ft_putstr_fd(" | M[1][3] = ", _camera->fd);
	ft_putnbr_fd(_camera->matrix.M[1][3], _camera->fd);
	ft_putchar_fd('\n', _camera->fd);
	ft_putstr_fd("M[2][0] = ", _camera->fd);
	ft_putnbr_fd(_camera->matrix.M[2][0], _camera->fd);
	ft_putstr_fd(" | M[2][1] = ", _camera->fd);
	ft_putnbr_fd(_camera->matrix.M[2][1], _camera->fd);
	ft_putstr_fd(" | M[2][2] = ", _camera->fd);
	ft_putnbr_fd(_camera->matrix.M[2][2], _camera->fd);
	ft_putstr_fd(" | M[2][3] = ", _camera->fd);
	ft_putnbr_fd(_camera->matrix.M[2][3], _camera->fd);
	ft_putchar_fd('\n', _camera->fd);
	ft_putstr_fd("M[3][0] = ", _camera->fd);
	ft_putnbr_fd(_camera->matrix.M[3][0], _camera->fd);
	ft_putstr_fd(" | M[3][1] = ", _camera->fd);
	ft_putnbr_fd(_camera->matrix.M[3][1], _camera->fd);
	ft_putstr_fd(" | M[3][2] = ", _camera->fd);
	ft_putnbr_fd(_camera->matrix.M[3][2], _camera->fd);
	ft_putstr_fd(" | M[3][3] = ", _camera->fd);
	ft_putnbr_fd(_camera->matrix.M[3][3], _camera->fd);
	ft_putstr_fd("\n\n", _camera->fd);
	// close(_camera->fd);

}

int main(int ac, char **av)
{
    t_minirt *miniRT;

	miniRT = ft_calloc(1, sizeof(t_minirt));
	miniRT->Data = ft_calloc(1, sizeof(t_data));
	if (ac > 1)
	{
		miniRT->file = av[1];
		miniRT->fd = open(miniRT->file, O_RDONLY);
		fill_data(miniRT->Data, &miniRT->Data->shape, miniRT->fd);
		// miniRT->Ambient = ft_calloc(1, sizeof(t_Ambient));
		// miniRT->Camera = ft_calloc(1, sizeof(t_Camera));
		// miniRT->Light = ft_calloc(1, sizeof(t_Light));
		miniRT->Mlx = ft_calloc(1, sizeof(t_mlx));
		fill_Info(miniRT);
		miniRT->Camera-> fd = open("had.txt", O_CREAT | O_RDWR, 777);
		fill_matrix(miniRT->Camera);
		print_matrix(miniRT->Camera);
		miniRT->Mlx->width = WIDTH;
		miniRT->Mlx->height = HEIGHT;
		miniRT->Mlx->mlx = mlx_init();
		miniRT->Mlx->win = mlx_new_window(miniRT->Mlx->mlx, WIDTH, HEIGHT, "miniRT");
		miniRT->Mlx->img = mlx_new_image(miniRT->Mlx->mlx, WIDTH, HEIGHT );
		miniRT->Mlx->addr = mlx_get_data_addr(miniRT->Mlx->img, &miniRT->Mlx->bits_per_pixel, &miniRT->Mlx->line_length, &miniRT->Mlx->endian);
		ray_render(miniRT);
		setup_controls(miniRT);
		mlx_loop(miniRT->Mlx->mlx);
	}
	// close ()
	return	0;
    // free_mini(miniRT);
}
