/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-jao <mait-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 18:17:03 by mait-jao          #+#    #+#             */
/*   Updated: 2022/10/12 21:52:34 by mait-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_str(const char *str, char c)
{
	size_t	count;
	size_t	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			count++;
			while (str[i] && str[i] != c && str[i] != '\n')
				i++;
		}
		if (str[i])
			i++;
	}
	return (count);
}

static char	**ft_free(char **arry, size_t j)
{
	while (j > 0)
		free(arry[j--]);
	free(arry);
	return (NULL);
}

static char	**ft_spl_ito(char **arry, const char *s, char c)
{
	int		x;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	x = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && x < 0)
			x = i;
		else if ((s[i] == c || i == ft_strlen(s)) && x >= 0)
		{
			arry[j] = ft_str_begin_to_fin((char *)s, x, i);
			if (!arry[j])
				return (ft_free(arry, j));
			x = -1;
			j++;
		}
		i++;
	}
	arry[j] = 0;
	return (arry);
}

char	**ft_split(const char *s, char c)
{
	char	**arry;

	if (!s)
		return (NULL);
	arry = (char **)malloc(sizeof(char *) * (ft_count_str(s, c) + 1));
	if (!arry)
		return (NULL);
	arry = ft_spl_ito(arry, s, c);
	return (arry);
}