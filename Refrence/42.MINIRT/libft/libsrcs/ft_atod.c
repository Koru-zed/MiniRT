/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-jao <mait-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 15:22:19 by mait-jao          #+#    #+#             */
/*   Updated: 2022/11/12 22:32:29 by mait-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atod(const char *str)
{
	double	nb;
	double	comma;
	int		sign;

	nb = 0.0;
	comma = 0.0;
	sign = 1;
	while ((9 <= *str && *str <= 13) || (*str == 32))
		str++;
	if ((*str == '-') || (*str == '+'))
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
		nb = (nb * 10) + (*(str++) - 48);
	if (*str == '.')
	{
		while (*(++str) >= '0' && *str <= '9')
			comma = 0.0;
		while (*(--str) >= '0' && *str <= '9')
			comma = (comma + (*str - 48)) / 10.0;
	}
	return ((nb + comma) * sign);
}
