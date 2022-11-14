/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-jao <mait-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 11:11:22 by mait-jao          #+#    #+#             */
/*   Updated: 2022/11/12 22:32:28 by mait-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	res;
	size_t	source;

	res = 0;
	source = 0;
	while (dst[res] && res < dstsize)
		res++;
	while (src[source] && ((res + source + 1) < dstsize))
	{
		dst[res + source] = src[source];
		source++;
	}
	if (res != dstsize)
		dst[res + source] = '\0';
	return (res + ft_strlen(src));
}
