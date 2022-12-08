/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-jao <mait-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 12:33:08 by mait-jao          #+#    #+#             */
/*   Updated: 2022/12/08 19:32:01 by mait-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>
#include <stdio.h>

static void	check_valid(int *check)
{
	*check = -1;
	ft_putstr_fd("\033[1;91m# Bad value #", 1);
}

static char	*ft_at_d(char *str, double *signe, double *value)
{
	while (*str == '-' || *str == '+')
	{
		if (*str == '-')
			*signe = -*signe;
		str++;
	}
	while (*str && ft_isdigit(*str))
	{
		*value = (*value * 10.0) + (*str - '0');
		str++;
	}
	return (str);
}

double	ft_atod(const char *str, int *check)
{
	char	*s;
	double	value;
	double	power;
	double	signe;

	value = 0.0;
	power = 1.0;
	signe = 1.0;
	s = ft_at_d((char *)str, &signe, &value);
	if (*s == '.' && *(s + 1))
	{
		s++;
		while (*s && ft_isdigit(*s))
		{
			value = (value * 10.0) + (*s - '0');
			power++;
			s++;
		}
	}
	if (*s)
		check_valid(check);
	return (value * pow(10.0, -(power - 1)) * signe);
}
// Converet string to double and return indice of last char converted to double
