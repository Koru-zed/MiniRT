/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-jao <mait-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:04:49 by mait-jao          #+#    #+#             */
/*   Updated: 2022/12/08 19:35:08 by mait-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	return (new_point(-ps_x, ps_y, 1));
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
		HEIGHT, "MINI_RT");
	mini->mlx->img = mlx_new_image(mini->mlx->_mlx, WIDTH, HEIGHT);
	mini->mlx->addr = mlx_get_data_addr(mini->mlx->img, \
		&mini->mlx->bits_per_pixel, &mini->mlx->line_length, \
			&mini->mlx->endian);
}

void	ft_check_file(t_minirt *mini)
{
    int		i;
	char	*str;

	str = mini->file;
	i = ft_strlen(str);
	mini->check = -1;
	if (i > 3 && str[i - 1] == 't' && str[i - 2] == 'r' && str[i - 3] == '.')
	{
		mini->fd = open(str, O_RDONLY);
		if (mini->fd > 0)
			mini->check = 1;
	}
	if (mini->check == -1)
	{
		ft_putstr_fd("\033[1;91mPath not valid", 2);
		exit(EXIT_FAILURE);
	}
	mini->check = 0;
}

int	main(int ac, char **av)
{
	t_minirt	*mini_rt;

	mini_rt = ft_calloc(1, sizeof(t_minirt));
	mini_rt->data = ft_calloc(1, sizeof(t_data));
	if (ac > 1)
	{
		mini_rt->file = av[1];
		ft_check_file(mini_rt);
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
