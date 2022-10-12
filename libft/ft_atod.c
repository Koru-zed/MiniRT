/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-jao <mait-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 12:33:08 by mait-jao          #+#    #+#             */
/*   Updated: 2022/10/12 16:38:52 by mait-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"
#include <math.h>

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
			signe *= -1;
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
