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
	return (new_point(-ps_x, ps_y, 1));
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

// zoom 
/*
		mini->Camera->matrix.M[0][2] = mini->Camera->ray.direction.x;
		mini->Camera->matrix.M[1][2] = mini->Camera->ray.direction.y;
		mini->Camera->matrix.M[2][2] = mini->Camera->ray.direction.z;
*/

void edit_camera(t_minirt *mini, int key)
{
	// printf("Camera\n");
	mini->Mlx->_do = 1; 
	if (key == KEYUP)
		mini->Camera->ray.origin.y -= 0.5;
	else if (key == KEYDOWN)
		mini->Camera->ray.origin.y += 0.5;
	else if (key == KEYLEFT)
		mini->Camera->ray.origin.x -= 0.5;
	else if (key == KEYRIGHT)
		mini->Camera->ray.origin.x += 0.5;
	else if (key == KEY_A || key == KEY_D || key == KEY_S || key == KEY_W)
	{
		if (key == KEY_A)
			mini->Camera->matrix = cross_matrix(update_matrix_y(-3.6), mini->Camera->matrix);
		else if (key == KEY_D)
			mini->Camera->matrix = cross_matrix(update_matrix_y(3.6),  mini->Camera->matrix);
		else if (key == KEY_W)
			mini->Camera->matrix = cross_matrix(update_matrix_x(3.6), mini->Camera->matrix);
		else if (key == KEY_D)
			mini->Camera->matrix = cross_matrix(update_matrix_x(-3.6),  mini->Camera->matrix);
		// printf("cross_matrix\n");
		// print_matrix(mini->Camera->matrix);
		mini->Camera->ray.direction.x = mini->Camera->matrix.M[2][0];
		mini->Camera->ray.direction.y = mini->Camera->matrix.M[2][1];
		mini->Camera->ray.direction.z = mini->Camera->matrix.M[2][2];
		// printf("x[%f], y{%f}, z{%f}", mini->Camera->ray.direction.x,mini->Camera->ray.direction.y,mini->Camera->ray.direction.z);

	}
	else
		mini->Mlx->_do = 0; 
}

// void edit_light(t_minirt *mini, int key)
// {

// }

void edit_sepher(t_minirt *mini, int key)
{
	int i;

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

	
	if (key == ROTATE_X)
		mini->Mlx->rotate = ROTATE_X;
	else if (key == ROTATE_Y)
		mini->Mlx->rotate = ROTATE_Y;
	else if (key == ROTATE_Z)
		mini->Mlx->rotate = ROTATE_Z;
	return (0);
}

void edit_plane(t_minirt *mini, int key)
{
	int i;
 
	mini->Mlx->_do = 1;
	if (key == KEYUP){
		i = -1;
		while (++i < mini->Data->shape.pl)
			mini->Plane[i].ray.origin.y += 0.75;
	}
	else if (key == KEYDOWN){
		i = -1;
		while (++i < mini->Data->shape.pl)
			mini->Plane[i].ray.origin.y -= 0.75;
	}
	else if (key == KEYLEFT){
		i = -1;
		while (++i < mini->Data->shape.pl)
			mini->Plane[i].ray.origin.x += 0.75;
	}
	else if (key == KEYRIGHT)
	{
		i = -1;
		while (++i < mini->Data->shape.pl)
			mini->Plane[i].ray.origin.x -= 0.75;
	}
	else if (key == R_RIGHT)
		rotation_plane(mini, 1);
	else if (key == R_LEFT)
		rotation_plane(mini, -1);
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
		// printf("hello\n");
		// print_matrix(mini->Camera);
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



void	rotation_plane(t_minirt *mini, int e)
{
	mini->Mlx->_do = 1;
	if (e == 1)
	{
		if (mini->Mlx->rotate == ROTATE_X && mini->Plane->ray.direction.x < 1.000000)
			mini->Plane->ray.direction.x += 0.1f * e;//cycle * e;
		else if (mini->Mlx->rotate == ROTATE_Y && mini->Plane->ray.direction.y < 1.000000)
			mini->Plane->ray.direction.y += 0.1f * e;// cycle * e;
		else if (mini->Mlx->rotate == ROTATE_Z && mini->Plane->ray.direction.z < 1.000000)
			mini->Plane->ray.direction.z += 0.1f * e;// cycle * e;
	}
	else if (e == -1)
	{
		if (mini->Mlx->rotate == ROTATE_X && mini->Plane->ray.direction.x >= -1.000000)
			mini->Plane->ray.direction.x += 0.1f * e;//cycle * e;
		else if (mini->Mlx->rotate == ROTATE_Y && mini->Plane->ray.direction.y >= -1.000000)
			mini->Plane->ray.direction.y += 0.1f * e;// cycle * e;
		else if (mini->Mlx->rotate == ROTATE_Z && mini->Plane->ray.direction.z >= -1.000000)
			mini->Plane->ray.direction.z += 0.1f * e;// cycle * e;
	}
	// printf("Plane->normal.x = %f, Plane->normal.y = %f, Plane->normal.z = %f\n", mini->Plane->ray.direction.x, mini->Plane->ray.direction.y, mini->Plane->ray.direction.z);
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
	else if (key == KEY_A)
		edit_mini(mini, key);
	else if (key == KEY_D)
		edit_mini(mini, key);
	else if (key == KEY_W)
		edit_mini(mini, key);
	else if (key == KEY_S)
		edit_mini(mini, key);
	else if (key == ZERO)
	{
		mini->Mlx->obj = 0;
		mini->Mlx->rotate = 0;
		mini->Mlx->_do = -1;
	}
	objs_key(key, mini);
	rotation_key(key, mini);
	// printf("key_press{%d} | rotate {%d} | shape{%d}\n", key, mini->Mlx->rotate, mini->Mlx->obj);
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

void print_matrix(t_matrix matrix)
{
	printf("########\n");
	printf("M[0][0] = ");
	printf("%f", matrix.M[0][0]);
	printf(" | M[0][1] = ");
	printf("%f", matrix.M[0][1]);
	printf(" | M[0][2] = ");
	printf("%f", matrix.M[0][2]);
	printf(" | M[0][3] = ");
	printf("%f", matrix.M[0][3]);
	printf("\n");
	printf("M[1][0] = ");
	printf("%f", matrix.M[1][0]);
	printf(" | M[1][1] = ");
	printf("%f", matrix.M[1][1]);
	printf(" | M[1][2] = ");
	printf("%f", matrix.M[1][2]);
	printf(" | M[1][3] = ");
	printf("%f", matrix.M[1][3]);
	printf("\n");
	printf("M[2][0] = ");
	printf("%f", matrix.M[2][0]);
	printf(" | M[2][1] = ");
	printf("%f", matrix.M[2][1]);
	printf(" | M[2][2] = ");
	printf("%f", matrix.M[2][2]);
	printf(" | M[2][3] = ");
	printf("%f", matrix.M[2][3]);
	printf("\n");
	printf("M[3][0] = ");
	printf("%f", matrix.M[3][0]);
	printf(" | M[3][1] = ");
	printf("%f", matrix.M[3][1]);
	printf(" | M[3][2] = ");
	printf("%f", matrix.M[3][2]);
	printf(" | M[3][3] = ");
	printf("%f", matrix.M[3][3]);
	printf("\n\n");;
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
		miniRT->Mlx = ft_calloc(1, sizeof(t_mlx));
		fill_Info(miniRT);
		// miniRT->Camera-> fd = open("had.txt", O_CREAT | O_RDWR, 777);
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
