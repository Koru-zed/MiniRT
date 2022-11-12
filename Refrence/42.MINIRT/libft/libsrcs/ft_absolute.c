/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_absolute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-jao <mait-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 19:32:57 by mait-jao          #+#    #+#             */
/*   Updated: 2022/11/12 22:32:28 by mait-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_absolute_int(int nb)
{
	if ((double)nb > 2147483647 || (double)nb < -2147483748)
		return (-1);
	if (nb < 0)
		nb *= -1;
	return (nb);
}

double	ft_absolute_decimal(double nb)
{
	if (nb < 0)
		nb *= -1;
	return (nb);
}
