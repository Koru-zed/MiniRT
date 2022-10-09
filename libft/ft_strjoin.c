/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-jao <mait-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 08:49:36 by mait-jao          #+#    #+#             */
/*   Updated: 2022/10/08 17:27:01 by mait-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_l;
	size_t	s2_l;
	char	*d;

	if (!s1 || !s2)
		return (NULL);
	s1_l = ft_strlen(s1);
	s2_l = ft_strlen(s2);
	d = (char *)malloc(sizeof(char) * (s1_l + s2_l + 1));
	if (!d)
		return (NULL);
	ft_memcpy(d, s1, s1_l);
	ft_memcpy((d + s1_l), s2, s2_l);
	d[s1_l + s2_l] = '\0';
	return (d);
}
