/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-jao <mait-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 21:12:20 by mait-jao          #+#    #+#             */
/*   Updated: 2022/11/12 22:32:28 by mait-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_inpoint(const char *s1, const char *set)
{
	size_t	s1_len;
	size_t	i;

	s1_len = ft_strlen(s1);
	i = 0;
	while (i < s1_len)
	{
		if (ft_strchr(set, s1[i]) == 0)
			break ;
		i++;
	}
	return (i);
}

static int	ft_outpoint(const char *s1, const char *set)
{
	size_t	s1_len;
	size_t	i;

	s1_len = ft_strlen(s1);
	i = 0;
	while (i < s1_len)
	{
		if (ft_strchr(set, s1[s1_len - i - 1]) == 0)
			break ;
		i++;
	}
	return (s1_len - i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		in;
	int		out;
	char	*trim;

	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return (ft_strdup(s1));
	in = ft_inpoint(s1, set);
	out = ft_outpoint(s1, set);
	if (in >= out)
		return (ft_strdup(""));
	trim = (char *)malloc(sizeof(char) * (out - in + 1));
	if (!trim)
		return (NULL);
	ft_strlcpy(trim, s1 + in, out - in + 1);
	return (trim);
}
