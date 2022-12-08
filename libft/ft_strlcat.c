/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <ael-mous@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 09:06:26 by mait-jao          #+#    #+#             */
/*   Updated: 2022/12/08 22:46:12 by ael-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const	char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	len;
	size_t	d_l;
	size_t	s_l;

	i = 0;
	j = 0;
	if (!dst && !dstsize)
		return (ft_strlen(src));
	s_l = ft_strlen(src);
	d_l = ft_strlen(dst);
	if (d_l < dstsize)
	{
		len = d_l + s_l;
		while (src[i] && d_l + i < dstsize - 1)
			dst[d_l + j++] = src[i++];
	}
	else
		return (dstsize + s_l);
	dst[d_l + i] = '\0';
	return (len);
}
