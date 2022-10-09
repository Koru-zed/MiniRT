/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-jao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 10:32:58 by mait-jao          #+#    #+#             */
/*   Updated: 2021/11/19 07:41:22 by mait-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_cmp(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	first;
	size_t	last;
	size_t	i;
	char	*d;

	if (!s1)
		return (NULL);
	i = 0;
	first = 0;
	last = ft_strlen(s1);
	while (s1[first] && ft_cmp(set, s1[first]))
		first++;
	while (last > first && ft_cmp(set, s1[last - 1]))
		last--;
	d = (char *)malloc((last - first + 1) * sizeof(char));
	if (!d)
		return (NULL);
	while (first < last)
		d[i++] = s1[first++];
	d[i] = '\0';
	return (d);
}
