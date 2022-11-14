/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putcollection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-jao <mait-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 23:31:00 by mait-jao          #+#    #+#             */
/*   Updated: 2022/11/12 22:32:28 by mait-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	pf_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	pf_putchar(char c)
{
	return (write (1, &c, 1));
}

int	pf_putstr(char *str)
{
	if (str == NULL)
		return (write (1, "(null)", 6));
	return (write (1, str, pf_strlen(str)));
}
