/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-jao <mait-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 18:12:07 by mait-jao          #+#    #+#             */
/*   Updated: 2022/12/08 21:49:51 by mait-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_n_max_min(int i)
{
	if (i == -1)
		return (0);
	return (-1);
}

int	ft_my_atoi(const char *str, int *check)
{
	int				signe;
	unsigned long	n;

	n = 0;
	signe = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			signe = -signe;
		str++;
	}
	while (ft_isdigit(*str))
	{
		n = (n * 10) + (*str - '0');
		if (n > 9223372036854775807)
			return (ft_n_max_min(signe));
		str++;
	}
	if (*str)
		*check = -1;
	return (n * signe);
}
