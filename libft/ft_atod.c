/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <ael-mous@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 12:33:08 by mait-jao          #+#    #+#             */
/*   Updated: 2022/11/29 16:56:45 by ael-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"
#include <math.h>
#include <stdio.h>

double	ft_atod(const char *str, int *check)
{
	double	value;
    double  power;
	double	signe;

	value = 0.0;
    power = 1.0;
	signe = 1.0;
	while (*str == '-' || *str == '+')
	{
		if (*str == '-')
			signe = -signe;
        str++;
	}
	while (*str && ft_isdigit(*str))
	{
		value = (value * 10.0) + (*str - '0');
		str++;
	}
    if (*str == '.' && *(str + 1))
	{
		str++;
		while (*str && ft_isdigit(*str))
		{
			value = (value * 10.0) + (*str - '0');
			power++;
			str++;
		}
	}
    if (*str)
    {
		*check = -1;
        ft_putstr_fd("# Bad value #", 1);
        exit(EXIT_FAILURE);
    }
	return (value * pow(10.0, -(power - 1)) * signe);
}
// Converet string to double and return indice of last char converted to double
