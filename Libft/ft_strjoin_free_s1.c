/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free_s1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-jao <mait-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 17:23:34 by mait-jao          #+#    #+#             */
/*   Updated: 2022/10/08 17:24:04 by mait-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free_s1(char *s1, char *s2)
{
	int		i;
	int		j;
	int		len;
	char	*d;

	if (!s1)
	{
		s1 = (char *)malloc(sizeof(char));
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	d = (char *)malloc(sizeof(char) * (len + 1));
	if (!d)
		return (NULL);
	i = -1;
	while (s1[++i])
		d[i] = s1[i];
	j = 0;
	while (s2[j])
		d[i++] = s2[j++];
	d[len] = '\0';
	free(s1);
	return (d);
}
