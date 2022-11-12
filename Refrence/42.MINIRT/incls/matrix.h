/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-jao <mait-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 13:24:59 by mait-jao          #+#    #+#             */
/*   Updated: 2022/11/12 22:32:27 by mait-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include "scene.h"
# include "vector_3d.h"

t_matrix	new_matrix(t_vec3 origin, t_vec3 forward, t_vec3 right, t_vec3 up);
t_matrix	matrix_identity(void);
t_matrix	matrix_product(t_matrix src, t_matrix mult);
t_vec3		multiply_by_matrix(t_vec3 p, t_matrix m);
t_matrix	matrix_rot_x(double degrees);
t_matrix	matrix_rot_y(double degrees);
void		matrix_look_at(t_scene *s);

#endif