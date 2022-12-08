#include "Include/miniRT.h"

t_point	ray_pixel_to_world(t_minirt *mini, int x, int y)
{
	double	aspect_ratio;
	double	half_hight;
	double	half_width;
	double	ps_x;
	double	ps_y;

	half_hight = tan((double)((double)mini->camera->fov * M_PI / 180) / 2);
	aspect_ratio = (double)mini->mlx->width / (double)mini->mlx->height;
	half_width = half_hight * aspect_ratio;
	ps_x = (double)(2 * (x + 0.5) / mini->mlx->width - 1) * half_width;
	ps_y = (double)(1 - 2 * (y + 0.5) / mini->mlx->height) * half_hight;
	return (new_point(ps_x, ps_y, 1));
}

t_ray	ray_generator(t_minirt *mini, int x, int y)
{
	t_point	shooting_direction;
	t_ray	ray;

	shooting_direction = ray_pixel_to_world(mini, x, y);
	shooting_direction = mul_point_matrix(shooting_direction, \
		mini->camera->matrix);
	shooting_direction = v_sub(shooting_direction, mini->camera->ray.origin);
	shooting_direction = normalizing(shooting_direction);
	ray.origin = mini->camera->ray.origin;
	ray.direction = shooting_direction;
	return (ray);
}

void	rotate_camera(t_minirt *mini, int key)
{
	t_point	direction;

	direction = mini->camera->ray.direction;
	if (key == KEYLEFT && mini->mlx->rotate == ROTATE_X)
		direction = mul_point_matrix(direction, update_matrix_y(-3.6));
	else if (key == KEYRIGHT && mini->mlx->rotate == ROTATE_X)
		direction = mul_point_matrix(direction, update_matrix_y(3.6));
	else if (key == KEYUP && mini->mlx->rotate == ROTATE_Y && \
			direction.z > EPSILON)
		direction = mul_point_matrix(direction, update_matrix_x(-3.6));
	else if (key == KEYDOWN && mini->mlx->rotate == ROTATE_Y && \
			direction.z > EPSILON)
		direction = mul_point_matrix(direction, update_matrix_x(3.6));
	else if (key == KEYUP && mini->mlx->rotate == ROTATE_Y && \
			direction.z < EPSILON)
		direction = mul_point_matrix(direction, update_matrix_x(3.6));
	else if (key == KEYDOWN && mini->mlx->rotate == ROTATE_Y && \
			direction.z < EPSILON)
		direction = mul_point_matrix(direction, update_matrix_x(-3.6));
}

void	edit_camera(t_minirt *mini, int key)
{
	t_matrix	matrix;

	mini->mlx->_do = 1;
	matrix = mini->camera->matrix;
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
		rotate_camera(mini, key);
	else
		mini->mlx->_do = 0;
}

void	edit_light(t_minirt *mini, int key)
{
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

void	edit_sepher(t_minirt *mini, int key)
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

int	rotation_key(int key, t_minirt *mini)
{
	if (key == ROTATE_X)
		mini->mlx->rotate = ROTATE_X;
	else if (key == ROTATE_Y)
		mini->mlx->rotate = ROTATE_Y;
	else if (key == ROTATE_Z)
		mini->mlx->rotate = ROTATE_Z;
	return (0);
}

void	edit_plane(t_minirt *mini, int key)
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

void	edit_cylinder(t_minirt *mini, int key)
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

void	edit_mini(t_minirt *mini, int key)
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
	if (mini->mlx->_do)
	{
		mlx_clear_window(mini->mlx->_mlx, mini->mlx->win);
		ray_render(mini);
	}
}

void	ft_print_vector(const t_point p)
{
	printf("p.x[%f] | p.y[%f] | p.z[%f]\n", p.x, p.y, p.z);
}

void	rotation_cylinder(t_minirt *mini, int key)
{
	int		i;
	t_point	direction;

	i = mini->mlx->obj.index;
	direction = mini->cylinder[i].ray.direction;
	if (key == KEYLEFT && mini->mlx->rotate == ROTATE_X)
		direction = mul_point_matrix(direction, update_matrix_y(-3.6));
	else if (key == KEYRIGHT && mini->mlx->rotate == ROTATE_X)
		direction = mul_point_matrix(direction, update_matrix_y(3.6));
	else if (key == KEYUP && mini->mlx->rotate == ROTATE_Y)
		direction = mul_point_matrix(direction, update_matrix_x(3.6));
	else if (key == KEYDOWN && mini->mlx->rotate == ROTATE_Y)
		direction = mul_point_matrix(direction, update_matrix_x(-3.6));
}

void	rotation_plane(t_minirt *mini, int key)
{
	int		i;
	t_point	direction;

	i = mini->mlx->obj.index;
	direction = mini->plane[i].ray.direction;
	if (key == KEYLEFT && mini->mlx->rotate == ROTATE_X)
		direction = mul_point_matrix(direction, update_matrix_y(-3.6));
	else if (key == KEYRIGHT && mini->mlx->rotate == ROTATE_X)
		direction = mul_point_matrix(direction, update_matrix_y(3.86));
	else if (key == KEYUP && mini->mlx->rotate == ROTATE_Y)
		direction = mul_point_matrix(direction, update_matrix_x(3.6));
	else if (key == KEYDOWN && mini->mlx->rotate == ROTATE_Y)
		direction = mul_point_matrix(direction, update_matrix_x(-3.6));
}

int	press_key(int key, t_minirt *mini)
{
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
	else if (key == DESTROY)
		free_mini(mini);
	else if (key == ZERO)
	{
		mini->mlx->obj.object = 0;
		mini->mlx->obj.index = 0;
		mini->mlx->rotate = 0;
		mini->mlx->_do = -1;
	}
	rotation_key(key, mini);
	return (0);
}

void	scroll_up(t_minirt *mini)
{
	int	i;

	mini->mlx->_do = 1;
	i = mini->mlx->obj.index;
	if (!mini->mlx->obj.object && mini->camera->fov > 0)
		mini->camera->fov -= 5;
	else if (mini->mlx->obj.object == _SEPHER && \
		(mini->sphere[i].radius - 0.5) > EPSILON)
		mini->sphere[i].radius -= 0.5;
	else if (mini->mlx->obj.object == _CYLINDER && \
		(mini->cylinder[i].redius - 0.5) >= EPSILON && \
			(mini->cylinder[i].height - 1) >= EPSILON)
	{
		mini->cylinder[i].redius -= 0.5;
		mini->cylinder[i].height -= 1;
	}
}

void	scroll_down(t_minirt *mini)
{
	int	i;

	mini->mlx->_do = 1;
	i = mini->mlx->obj.index;
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

int	ft_mouse(int scroll, int x, int y, t_minirt *mini)
{
	int	i;

	mini->mlx->_do = 0;
	i = mini->mlx->obj.index;
	if (scroll == 1)
	{
		mini->mlx->mouse = 1;
		mini->mlx->rotate = 0;
		intersection_over_objects(mini, ray_generator(mini, x, y));
		mini->mlx->mouse = 0;
	}
	else if (scroll == 4)
		scroll_up(mini);
	else if (scroll == 5)
		scroll_down(mini);
	if (mini->mlx->_do)
	{
		mlx_clear_window(mini->mlx->_mlx, mini->mlx->win);
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

void	init_mlx(t_minirt *mini)
{
	mini->mlx = ft_calloc(1, sizeof(t_mlx));
	mini->mlx->width = WIDTH;
	mini->mlx->height = HEIGHT;
	mini->mlx->_mlx = mlx_init();
	mini->mlx->win = mlx_new_window(mini->mlx->_mlx, WIDTH, \
		HEIGHT, "mini_rt");
	mini->mlx->img = mlx_new_image(mini->mlx->_mlx, WIDTH, HEIGHT);
	mini->mlx->addr = mlx_get_data_addr(mini->mlx->img, \
		&mini->mlx->bits_per_pixel, &mini->mlx->line_length, \
			&mini->mlx->endian);
}

int	main(int ac, char **av)
{
	t_minirt	*mini_rt;

	mini_rt = ft_calloc(1, sizeof(t_minirt));
	mini_rt->data = ft_calloc(1, sizeof(t_data));
	if (ac > 1)
	{
		mini_rt->file = av[1];
		mini_rt->fd = open(mini_rt->file, O_RDONLY);
		fill_data(mini_rt->data, &mini_rt->data->shape, mini_rt->fd);
		fill_info(mini_rt);
		init_mlx(mini_rt);
		ray_render(mini_rt);
		setup_controls(mini_rt);
		mlx_loop(mini_rt->mlx->_mlx);
	}
	free_mini(mini_rt);
	return (0);
}
