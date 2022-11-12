/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-jao <mait-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 12:04:58 by mait-jao          #+#    #+#             */
/*   Updated: 2022/11/12 22:32:27 by mait-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incls/vector_array.h"

void	vector_free_elements(t_vector *v, void *del(void *))
{
	size_t	i;

	i = 0;
	while (i < v->total)
	{
		if (del != NULL)
		{
			del(v->elements[i]);
		}
		free(v->elements[i]);
		i++;
	}
	free(v->elements);
	v->elements = NULL;
}
