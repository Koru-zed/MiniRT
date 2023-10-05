/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-jao <mait-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 09:32:36 by mait-jao          #+#    #+#             */
/*   Updated: 2022/12/08 13:20:38 by mait-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*d1;
	unsigned char	*d2;

	i = 0;
	d1 = (unsigned char *)s1;
	d2 = (unsigned char *)s2;
	while (d1[i] && d2[i] && d1[i] == d2[i])
		i++;
	return (d1[i] - d2[i]);
}
