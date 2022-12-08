/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_begin_to_fin.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-jao <mait-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 13:20:05 by mait-jao          #+#    #+#             */
/*   Updated: 2022/12/08 13:20:06 by mait-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_str_begin_to_fin(char *str, int begin, int fin)
{
	int		i;
	char	*dst;

	if (!str)
		return (NULL);
	i = 0;
	if (fin - begin == 0)
		return (NULL);
	dst = ft_calloc(sizeof(char), (fin - begin + 1));
	if (!dst)
		return (NULL);
	while (begin < fin)
		dst[i++] = str[begin++];
	dst[i] = '\0';
	return (dst);
}
