/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <ael-mous@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 21:26:41 by mait-jao          #+#    #+#             */
/*   Updated: 2022/12/08 22:47:04 by ael-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*d;

	i = 0;
	d = NULL;
	if (!s)
		return (NULL);
	if (len <= ft_strlen(s))
		d = (char *)malloc(sizeof(char) * (len + 1));
	else if (len > ft_strlen(s))
		d = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!d)
		return (NULL);
	while (i < len && i < ft_strlen(s) && start < ft_strlen(s))
	{
		d[i] = s[start + i];
		i++;
	}
	d[i] = '\0';
	return (d);
}
