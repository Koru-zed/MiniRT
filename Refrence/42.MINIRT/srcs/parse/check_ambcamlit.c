/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ambcamlit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-jao <mait-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 15:20:50 by mait-jao          #+#    #+#             */
/*   Updated: 2022/11/12 22:32:27 by mait-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incls/mini_rt.h"

void	check_amb_cam_lit(t_scene *scene)
{
	if (scene->amb == NULL || scene->cam == NULL || scene->lit == NULL)
		print_error_exit(scene, "Missing Ambiant, Camera or Light");
}

void	check_one_amb(t_scene *scene)
{
	if (scene->amb != NULL)
		print_error_exit(scene, "Max one Ambiant light [A]");
}

void	check_one_cam(t_scene *scene)
{
	if (scene->cam != NULL)
		print_error_exit(scene, "Max one Camera [C]");
}

void	check_one_lit(t_scene *scene)
{
	if (scene->lit != NULL)
		print_error_exit(scene, "Max one Light source [L]");
}
