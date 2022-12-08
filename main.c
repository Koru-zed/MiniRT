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

	half_hight = tanf((double )((double )mini->camera->fov * M_PI / 180) / 2);
	aspect_ratio = (double)mini->mlx->width / (double)mini->mlx->height;
	half_width = half_hight * aspect_ratio;
	ps_x = (double )(2 * (x + 0.5) / mini->mlx->width - 1) * half_width;
	ps_y = (double )(1 - 2 * (y + 0.5) / mini->mlx->height) * half_hight;
	return (new_point(ps_x, ps_y, 1));
}

t_ray	ray_generator(t_minirt *mini, int x, int y)
{
	t_point	shooting_direction;
	t_ray	ray;

	shooting_direction = ray_pixel_to_world(mini, x, y);
	shooting_direction = mul_point_matrix(shooting_direction, mini->camera->matrix);
	shooting_direction = v_sub(shooting_direction, mini->camera->ray.origin);
	shooting_direction = normalizing(shooting_direction);
	ray.origin = mini->camera->ray.origin;
	ray.direction = shooting_direction;
	return (ray);
}

void edit_camera(t_minirt *mini, int key)
{
	t_matrix matrix;
	matrix = mini->camera->matrix;
	mini->mlx->_do = 1;
	if (!mini->mlx->rotate)
	{
		if (key == KEYUP)
			mini->camera->ray.origin.y -= 0.5;
		else if (key == KEYDOWN)
			mini->camera->ray.origin.y += 0.5;
		else if (key == KEYLEFT)
			mini->camera->ray.origin.x -= 0.5;
		else if (key == KEYRIGHT)
			mini->camera->ray.origin.x += 0.5;
	}
	else if (mini->mlx->rotate)
	{
		if (key == KEYLEFT && mini->mlx->rotate == ROTATE_X)
			mini->camera->ray.direction = mul_point_matrix(mini->camera->ray.direction, update_matrix_y(-3.6));
		else if (key == KEYRIGHT && mini->mlx->rotate == ROTATE_X)
			mini->camera->ray.direction = mul_point_matrix(mini->camera->ray.direction, update_matrix_y(3.6));
		else if (key == KEYUP && mini->mlx->rotate == ROTATE_Y && mini->camera->ray.direction.z > EPSILON)
			mini->camera->ray.direction = mul_point_matrix(mini->camera->ray.direction, update_matrix_x(-3.6));
		else if (key == KEYDOWN && mini->mlx->rotate == ROTATE_Y && mini->camera->ray.direction.z > EPSILON)
			mini->camera->ray.direction = mul_point_matrix(mini->camera->ray.direction, update_matrix_x(3.6));
		else if (key == KEYUP && mini->mlx->rotate == ROTATE_Y && mini->camera->ray.direction.z < EPSILON)
			mini->camera->ray.direction = mul_point_matrix(mini->camera->ray.direction, update_matrix_x(3.6));
		else if (key == KEYDOWN && mini->mlx->rotate == ROTATE_Y && mini->camera->ray.direction.z < EPSILON)
			mini->camera->ray.direction = mul_point_matrix(mini->camera->ray.direction, update_matrix_x(-3.6));
	}
	else
		mini->mlx->_do = 0;
}

void edit_light(t_minirt *mini, int key)
{
	// printf("hello\n");
	mini->mlx->_do = 1;
	if (key == KEYUP)
		mini->light->cordinates.y += 0.75;
	else if (key == KEYDOWN)
		mini->light->cordinates.y -= 0.75;
	else if (key == KEYLEFT)
		mini->light->cordinates.x += 0.75;
	else if (key == KEYRIGHT)
		mini->light->cordinates.x -= 0.75;
	else
		mini->mlx->_do = 0;
}

void edit_sepher(t_minirt *mini, int key)
{
	mini->mlx->_do = 1;
	if (key == KEYUP)
		mini->sphere[mini->mlx->obj.index].center.y += 0.75;
	else if (key == KEYDOWN)
		mini->sphere[mini->mlx->obj.index].center.y -= 0.75;
	else if (key == KEYLEFT)
		mini->sphere[mini->mlx->obj.index].center.x += 0.75;
	else if (key == KEYRIGHT)
		mini->sphere[mini->mlx->obj.index].center.x -= 0.75;
	else
		mini->mlx->_do = 0;

}

int rotation_key(int key, t_minirt *mini)
{
	if (key == ROTATE_X)
		mini->mlx->rotate = ROTATE_X;
	else if (key == ROTATE_Y)
		mini->mlx->rotate = ROTATE_Y;
	else if (key == ROTATE_Z)
		mini->mlx->rotate = ROTATE_Z;
	return (0);
}

void edit_plane(t_minirt *mini, int key)
{
	mini->mlx->_do = 1;
	if (mini->mlx->rotate)
		rotation_plane(mini, key);
	else if (key == KEYUP)
		mini->plane[mini->mlx->obj.index].ray.origin.y += 0.75;
	else if (key == KEYDOWN)
		mini->plane[mini->mlx->obj.index].ray.origin.y -= 0.75;
	else if (key == KEYLEFT)
		mini->plane[mini->mlx->obj.index].ray.origin.x += 0.75;
	else if (key == KEYRIGHT)
		mini->plane[mini->mlx->obj.index].ray.origin.x -= 0.75;
	else
		mini->mlx->_do = 0;
}

void edit_cylinder(t_minirt *mini, int key)
{
	mini->mlx->_do = 1;
	if (mini->mlx->rotate)
		rotation_cylinder(mini, key);
	else if (key == KEYUP)
		mini->cylinder[mini->mlx->obj.index].ray.origin.y += 0.75;
	else if (key == KEYDOWN)
		mini->cylinder[mini->mlx->obj.index].ray.origin.y -= 0.75;
	else if (key == KEYLEFT)
		mini->cylinder[mini->mlx->obj.index].ray.origin.x += 0.75;
	else if (key == KEYRIGHT)
		mini->cylinder[mini->mlx->obj.index].ray.origin.x -= 0.75;
	else
		mini->mlx->_do = 0;
}

void edit_mini(t_minirt *mini, int key)
{
	if (!mini->mlx->obj.object)
		edit_camera(mini, key);
	else if (mini->mlx->obj.object == _SEPHER)
		edit_sepher(mini, key);
	else if (mini->mlx->obj.object == _PLANE)
		edit_plane(mini, key);
	else if (mini->mlx->obj.object == _CYLINDER)
		edit_cylinder(mini, key);
	else if (mini->mlx->obj.object == _LIGHT)
		edit_light(mini, key);
	// mini->Mlx->addr = mlx_get_data_addr(mini->Mlx->img, &mini->Mlx->bits_per_pixel, &mini->Mlx->line_length, &mini->Mlx->endian);
	if (mini->mlx->_do)
	{
		mlx_clear_window(mini->mlx->mlx, mini->mlx->win);
		ray_render(mini);
	}

}
void		ft_print_vector(const t_point p)
{
	printf("p.x[%f] | p.y[%f] | p.z[%f]\n", p.x, p.y, p.z);
}
void	rotation_cylinder(t_minirt *mini, int key)
{
	int i;

	i = mini->mlx->obj.index;
	if (key == KEYLEFT && mini->mlx->rotate == ROTATE_X)
		mini->cylinder[i].ray.direction = mul_point_matrix(mini->cylinder[i].ray.direction, update_matrix_y(-3.6));
	else if (key == KEYRIGHT && mini->mlx->rotate == ROTATE_X)
		mini->cylinder[i].ray.direction = mul_point_matrix(mini->cylinder[i].ray.direction, update_matrix_y(3.6));
	else if (key == KEYUP && mini->mlx->rotate == ROTATE_Y)
		mini->cylinder[i].ray.direction = mul_point_matrix(mini->cylinder[i].ray.direction, update_matrix_x(3.6));
	else if (key == KEYDOWN && mini->mlx->rotate == ROTATE_Y)
		mini->cylinder[i].ray.direction = mul_point_matrix(mini->cylinder[i].ray.direction, update_matrix_x(-3.6));
	else if (key == KEYLEFT && mini->mlx->rotate == ROTATE_X && !mini->cylinder[i].ray.direction.y)
		mini->cylinder[i].ray.direction.y += (double)(2 / 360);
	else if (key == KEYRIGHT && mini->mlx->rotate == ROTATE_X && !mini->cylinder[i].ray.direction.y)
		mini->cylinder[i].ray.direction.y -= (double)(2 / 360);
	else if (key == KEYUP && mini->mlx->rotate == ROTATE_Y && !mini->cylinder[i].ray.direction.x)
		mini->cylinder[i].ray.direction.x += (double)(2 / 360);
	else if (key == KEYDOWN && mini->mlx->rotate == ROTATE_Y && !mini->cylinder[i].ray.direction.x)
		mini->cylinder[i].ray.direction.x += (double)(2 / 360);
}

void	rotation_plane(t_minirt *mini, int key)
{
	int i;

	i = mini->mlx->obj.index;
	if (key == KEYLEFT && mini->mlx->rotate == ROTATE_X)
	{
		ft_print_vector(mini->plane[i].ray.direction);
		mini->plane[i].ray.direction = mul_point_matrix(mini->plane[i].ray.direction, update_matrix_y(-3.6));
		ft_print_vector(mini->plane[i].ray.direction);
	}else if (key == KEYRIGHT && mini->mlx->rotate == ROTATE_X)
	{
		ft_print_vector(mini->plane[i].ray.direction);
		mini->plane[i].ray.direction = mul_point_matrix(mini->plane[i].ray.direction, update_matrix_y(3.86));
		ft_print_vector(mini->plane[i].ray.direction);
	}else if (key == KEYUP && mini->mlx->rotate == ROTATE_Y)
		mini->plane[i].ray.direction = mul_point_matrix(mini->plane[i].ray.direction, update_matrix_x(3.6));
	else if (key == KEYDOWN && mini->mlx->rotate == ROTATE_Y)
		mini->plane[i].ray.direction = mul_point_matrix(mini->plane[i].ray.direction, update_matrix_x(-3.6));
}


int press_key(int key, t_minirt *mini)
{
	printf("mini->obj.object[%d] | mini->obj.index[%d]\n", mini->mlx->obj.object, mini->mlx->obj.index);
	if (key == KEYUP)
		edit_mini(mini, key);
	else if (key == KEYDOWN)
		edit_mini(mini, key);
	else if (key == KEYLEFT)
		edit_mini(mini, key);
	else if (key == KEYRIGHT)
		edit_mini(mini, key);
	else if (key == _LIGHT)
		mini->mlx->obj.object = _LIGHT;
	else if (key == DESTROY   )
		free_mini(mini);
	else if (key == ZERO)
	{
		mini->mlx->obj.object = 0;
		mini->mlx->obj.index = 0;
		mini->mlx->rotate = 0;
		mini->mlx->_do = -1;
	}
	rotation_key(key, mini);
	printf("key_press{%d} | rotate {%d} | shape{%d}\n", key, mini->mlx->rotate, mini->mlx->obj.object);
	return (0);
}

int ft_mouse(int button, int x, int y, t_minirt *mini)
{
	int i;

	i = mini->mlx->obj.index;
	mini->mlx->_do = 0;
	if (button  == 1)
	{
		mini->mlx->mouse = 1;
			printf ("x[%d] | y[%d]\n", x, y);
		mini->mlx->rotate = 0;
		intersection_over_objects(mini, ray_generator(mini, x, y));
		mini->mlx->mouse = 0;
		if (mini->mlx->obj.object)
			printf("mini->obj.object[%d] | mini->obj.index[%d]\n", mini->mlx->obj.object, i);
	}
	else if (button  == 4)
    {
		mini->mlx->_do = 1;
		if (!mini->mlx->obj.object && mini->camera->fov > 0)
			mini->camera->fov -= 5;
		else if (mini->mlx->obj.object == _SEPHER && (mini->sphere[i].radius - 0.5) > EPSILON)
			mini->sphere[i].radius -= 0.5;
		else if (mini->mlx->obj.object == _CYLINDER && (mini->cylinder[i].redius - 0.5) >= EPSILON && (mini->cylinder[i].height - 1) >= EPSILON)
		{
			mini->cylinder[i].redius -= 0.5;
			mini->cylinder[i].height -= 1;
		}
	}
	else if (button  == 5)
    {
		mini->mlx->_do = 1;
		if (!mini->mlx->obj.object && mini->camera->fov <= 170)
			mini->camera->fov += 5;
		else if (mini->mlx->obj.object == _SEPHER)
			mini->sphere[i].radius += 0.5;
		else if (mini->mlx->obj.object == _CYLINDER)
		{
			mini->cylinder[i].redius += 0.5;
			mini->cylinder[i].height += 1;
		}
			
	}
	if (mini->mlx->_do)
	{
		mlx_clear_window(mini->mlx->mlx, mini->mlx->win);
		ray_render(mini);
	}
	return (0);
}

void	setup_controls(t_minirt *mini)
{
	mlx_hook(mini->mlx->win, 17, 0, free_mini, mini);
	mlx_hook(mini->mlx->win, 4, 0, ft_mouse, mini);
	mlx_hook(mini->mlx->win, 5, 0, ft_mouse, mini);
	mlx_key_hook(mini->mlx->win, press_key, mini);
	mlx_mouse_hook(mini->mlx->win, ft_mouse, mini);
}

void print_matrix(t_matrix matrix)
{
	printf("########\n");
	printf("M[0][0] = ");
	printf("%lf", matrix.m[0][0]);
	printf(" | M[0][1] = ");
	printf("%lf", matrix.m[0][1]);
	printf(" | M[0][2] = ");
	printf("%lf", matrix.m[0][2]);
	printf(" | M[0][3] = ");
	printf("%lf", matrix.m[0][3]);
	printf("\n");
	printf("M[1][0] = ");
	printf("%lf", matrix.m[1][0]);
	printf(" | M[1][1] = ");
	printf("%lf", matrix.m[1][1]);
	printf(" | M[1][2] = ");
	printf("%lf", matrix.m[1][2]);
	printf(" | M[1][3] = ");
	printf("%lf", matrix.m[1][3]);
	printf("\n");
	printf("M[2][0] = ");
	printf("%lf", matrix.m[2][0]);
	printf(" | M[2][1] = ");
	printf("%lf", matrix.m[2][1]);
	printf(" | M[2][2] = ");
	printf("%lf", matrix.m[2][2]);
	printf(" | M[2][3] = ");
	printf("%lf", matrix.m[2][3]);
	printf("\n");
	printf("M[3][0] = ");
	printf("%lf", matrix.m[3][0]);
	printf(" | M[3][1] = ");
	printf("%lf", matrix.m[3][1]);
	printf(" | M[3][2] = ");
	printf("%lf", matrix.m[3][2]);
	printf(" | M[3][3] = ");
	printf("%lf", matrix.m[3][3]);
	printf("\n\n");;
}

int main(int ac, char **av)
{
    t_minirt *miniRT;

	miniRT = ft_calloc(1, sizeof(t_minirt));
	miniRT->data = ft_calloc(1, sizeof(t_data));
	if (ac > 1)
	{
		miniRT->file = av[1]; // todo check for the extension  ".rt"
		miniRT->fd = open(miniRT->file, O_RDONLY);
		if (miniRT->fd == -1)
		{
			perror(miniRT->file);
			free(miniRT->data);
			free(miniRT);
			return (EXIT_FAILURE);
		}
		fill_data(miniRT->data, &miniRT->data->shape, miniRT->fd);
		miniRT->mlx = ft_calloc(1, sizeof(t_mlx));
		fill_info(miniRT);
		miniRT->mlx->width = WIDTH;
		miniRT->mlx->height = HEIGHT;
		miniRT->mlx->mlx = mlx_init();
		miniRT->mlx->win = mlx_new_window(miniRT->mlx->mlx, WIDTH, HEIGHT, "miniRT");
		miniRT->mlx->img = mlx_new_image(miniRT->mlx->mlx, WIDTH, HEIGHT);
		miniRT->mlx->addr = mlx_get_data_addr(miniRT->mlx->img, &miniRT->mlx->bits_per_pixel, &miniRT->mlx->line_length, &miniRT->mlx->endian);
		ray_render(miniRT);
		setup_controls(miniRT);
		mlx_loop(miniRT->mlx->mlx);
	}
    free_mini(miniRT);
	return	0;
}
