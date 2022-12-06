#include "Include/miniRT.h"


long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}


t_point	ray_pixel_to_world(t_minirt *mini, int x, int y)
{
	double	aspect_ratio;
	double	half_hight;
	double   half_width;
	double	ps_x;
	double	ps_y;

	half_hight = tanf((double )((double )mini->Camera->fov * M_PI / 180) / 2);
	aspect_ratio = (double)mini->Mlx->width / (double)mini->Mlx->height;
	half_width = half_hight * aspect_ratio;
	ps_x = (double )(2 * (x + 0.5) / mini->Mlx->width - 1) * half_width;
	ps_y = (double )(1 - 2 * (y + 0.5) / mini->Mlx->height) * half_hight;
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

void edit_camera(t_minirt *mini, int key)
{
	t_matrix matrix;
	matrix = mini->Camera->matrix;
	mini->Mlx->_do = 1;
	if (!mini->Mlx->rotate)
	{
		if (key == KEYUP)
			mini->Camera->ray.origin.y -= 0.5;
		else if (key == KEYDOWN)
			mini->Camera->ray.origin.y += 0.5;
		else if (key == KEYLEFT)
			mini->Camera->ray.origin.x -= 0.5;
		else if (key == KEYRIGHT)
			mini->Camera->ray.origin.x += 0.5;
	}
	else if (mini->Mlx->rotate)
	{
		if (key == KEYLEFT && mini->Mlx->rotate == ROTATE_X)
			mini->Camera->ray.direction = mul_point_matrix(mini->Camera->ray.direction, update_matrix_y(-3.6));
		else if (key == KEYRIGHT && mini->Mlx->rotate == ROTATE_X)
			mini->Camera->ray.direction = mul_point_matrix(mini->Camera->ray.direction, update_matrix_y(3.6));
		else if (key == KEYUP && mini->Mlx->rotate == ROTATE_Y && mini->Camera->ray.direction.z > EPSILON)
			mini->Camera->ray.direction = mul_point_matrix(mini->Camera->ray.direction, update_matrix_x(-3.6));
		else if (key == KEYDOWN && mini->Mlx->rotate == ROTATE_Y && mini->Camera->ray.direction.z > EPSILON)
			mini->Camera->ray.direction = mul_point_matrix(mini->Camera->ray.direction, update_matrix_x(3.6));
		else if (key == KEYUP && mini->Mlx->rotate == ROTATE_Y && mini->Camera->ray.direction.z < EPSILON)
			mini->Camera->ray.direction = mul_point_matrix(mini->Camera->ray.direction, update_matrix_x(3.6));
		else if (key == KEYDOWN && mini->Mlx->rotate == ROTATE_Y && mini->Camera->ray.direction.z < EPSILON)
			mini->Camera->ray.direction = mul_point_matrix(mini->Camera->ray.direction, update_matrix_x(-3.6));
	}
	else
		mini->Mlx->_do = 0; 
}

void edit_light(t_minirt *mini, int key)
{
	// printf("hello\n");
	mini->Mlx->_do = 1;
	if (key == KEYUP)
		mini->Light->cordinates.y += 0.75;
	else if (key == KEYDOWN)
		mini->Light->cordinates.y -= 0.75;
	else if (key == KEYLEFT)
		mini->Light->cordinates.x += 0.75;
	else if (key == KEYRIGHT)
		mini->Light->cordinates.x -= 0.75;
	else
		mini->Mlx->_do = 0;
}

void edit_sepher(t_minirt *mini, int key)
{
	mini->Mlx->_do = 1;
	if (key == KEYUP)
		mini->Sphere[mini->Mlx->obj.index].center.y += 0.75;
	else if (key == KEYDOWN)
		mini->Sphere[mini->Mlx->obj.index].center.y -= 0.75;
	else if (key == KEYLEFT)
		mini->Sphere[mini->Mlx->obj.index].center.x += 0.75;
	else if (key == KEYRIGHT)
		mini->Sphere[mini->Mlx->obj.index].center.x -= 0.75;
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
	mini->Mlx->_do = 1;
	if (mini->Mlx->rotate)
		rotation_plane(mini, key);
	else if (key == KEYUP)
		mini->Plane[mini->Mlx->obj.index].ray.origin.y += 0.75;
	else if (key == KEYDOWN)
		mini->Plane[mini->Mlx->obj.index].ray.origin.y -= 0.75;
	else if (key == KEYLEFT)
		mini->Plane[mini->Mlx->obj.index].ray.origin.x += 0.75;
	else if (key == KEYRIGHT)
		mini->Plane[mini->Mlx->obj.index].ray.origin.x -= 0.75;
	else
		mini->Mlx->_do = 0; 
}

void edit_mini(t_minirt *mini, int key)
{
	if (!mini->Mlx->obj.object)
		edit_camera(mini, key);
	else if (mini->Mlx->obj.object == _SEPHER)
		edit_sepher(mini, key);
	else if (mini->Mlx->obj.object == _PLANE)
		edit_plane(mini, key);
	else if (mini->Mlx->obj.object == _LIGHT)
		edit_light(mini, key);
	// else if (key == _CYLINDER)
	// 	edit_cylinder(mini, key);
	// mini->Mlx->addr = mlx_get_data_addr(mini->Mlx->img, &mini->Mlx->bits_per_pixel, &mini->Mlx->line_length, &mini->Mlx->endian);
	if (mini->Mlx->_do)
	{
		mlx_clear_window(mini->Mlx->mlx, mini->Mlx->win);
		ray_render(mini);
	}

}



void	rotation_plane(t_minirt *mini, int key)
{
	int i;

	i = mini->Mlx->obj.index;
	if (key == KEYLEFT && mini->Mlx->rotate == ROTATE_X)
		mini->Plane[i].ray.direction = mul_point_matrix(mini->Plane[i].ray.direction, update_matrix_y(-3.6));
	else if (key == KEYRIGHT && mini->Mlx->rotate == ROTATE_X)
		mini->Plane[i].ray.direction = mul_point_matrix(mini->Plane[i].ray.direction, update_matrix_y(3.6));
	else if (key == KEYUP && mini->Mlx->rotate == ROTATE_Y)
		mini->Plane[i].ray.direction = mul_point_matrix(mini->Plane[i].ray.direction, update_matrix_x(3.6));
	else if (key == KEYDOWN && mini->Mlx->rotate == ROTATE_Y)
		mini->Plane[i].ray.direction = mul_point_matrix(mini->Plane[i].ray.direction, update_matrix_x(-3.6));
}


int press_key(int key, t_minirt *mini)
{
	printf("mini->obj.object[%d] | mini->obj.index[%d]\n", mini->Mlx->obj.object, mini->Mlx->obj.index);
	if (key == KEYUP)
		edit_mini(mini, key);
	else if (key == KEYDOWN)
		edit_mini(mini, key);
	else if (key == KEYLEFT)
		edit_mini(mini, key);
	else if (key == KEYRIGHT)
		edit_mini(mini, key);
	else if (key == _LIGHT)
		mini->Mlx->obj.object = _LIGHT;
	else if (key == DESTROY || key == CLOSE)
		free_mini(mini);
	else if (key == ZERO)
	{
		mini->Mlx->obj.object = 0;
		mini->Mlx->obj.index = 0;
		mini->Mlx->rotate = 0;
		mini->Mlx->_do = -1;
	}
	rotation_key(key, mini);
	printf("key_press{%d} | rotate {%d} | shape{%d}\n", key, mini->Mlx->rotate, mini->Mlx->obj.object);
	return (0);
}

int ft_mouse(int button, int x, int y, t_minirt *mini)
{

	mini->Mlx->_do = 0;
	if (button  == 1)
	{
		mini->Mlx->mouse = 1;
			printf ("x[%d] | y[%d]\n", x, y);
		mini->Mlx->rotate = 0;
		intersection_over_objects(mini, ray_generator(mini, x, y));
		mini->Mlx->mouse = 0;
		if (mini->Mlx->obj.object)
			printf("mini->obj.object[%d] | mini->obj.index[%d]\n", mini->Mlx->obj.object, mini->Mlx->obj.index);
	}
	else if (button  == 4)
    {
		mini->Mlx->_do = 1;
		if (!mini->Mlx->obj.object && mini->Camera->fov > 0)
			mini->Camera->fov -= 5;
		else if (mini->Mlx->obj.object == _SEPHER && mini->Sphere->radius > 0)
			mini->Sphere->radius -= 0.5;
	}
	else if (button  == 5)
    {
		mini->Mlx->_do = 1;
		if (!mini->Mlx->obj.object && mini->Camera->fov <= 170)
			mini->Camera->fov += 5;
		else if (mini->Mlx->obj.object == _SEPHER)
			mini->Sphere->radius += 0.5;
			
	}
	if (mini->Mlx->_do)
	{
		mlx_clear_window(mini->Mlx->mlx, mini->Mlx->win);
		ray_render(mini);
	}
	return (0);
}

void	setup_controls(t_minirt *mini)
{
	mlx_mouse_hook(mini->Mlx->win, ft_mouse, mini);
	mlx_hook(mini->Mlx->win, 17, 0, free_mini, mini);
	mlx_hook(mini->Mlx->win, 4, 0, ft_mouse, mini);
	mlx_hook(mini->Mlx->win, 5, 0, ft_mouse, mini);
	mlx_key_hook(mini->Mlx->win, press_key, mini);
}

void print_matrix(t_matrix matrix)
{
	printf("########\n");
	printf("M[0][0] = ");
	printf("%lf", matrix.M[0][0]);
	printf(" | M[0][1] = ");
	printf("%lf", matrix.M[0][1]);
	printf(" | M[0][2] = ");
	printf("%lf", matrix.M[0][2]);
	printf(" | M[0][3] = ");
	printf("%lf", matrix.M[0][3]);
	printf("\n");
	printf("M[1][0] = ");
	printf("%lf", matrix.M[1][0]);
	printf(" | M[1][1] = ");
	printf("%lf", matrix.M[1][1]);
	printf(" | M[1][2] = ");
	printf("%lf", matrix.M[1][2]);
	printf(" | M[1][3] = ");
	printf("%lf", matrix.M[1][3]);
	printf("\n");
	printf("M[2][0] = ");
	printf("%lf", matrix.M[2][0]);
	printf(" | M[2][1] = ");
	printf("%lf", matrix.M[2][1]);
	printf(" | M[2][2] = ");
	printf("%lf", matrix.M[2][2]);
	printf(" | M[2][3] = ");
	printf("%lf", matrix.M[2][3]);
	printf("\n");
	printf("M[3][0] = ");
	printf("%lf", matrix.M[3][0]);
	printf(" | M[3][1] = ");
	printf("%lf", matrix.M[3][1]);
	printf(" | M[3][2] = ");
	printf("%lf", matrix.M[3][2]);
	printf(" | M[3][3] = ");
	printf("%lf", matrix.M[3][3]);
	printf("\n\n");;
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
    free_mini(miniRT);
	return	0;
}
