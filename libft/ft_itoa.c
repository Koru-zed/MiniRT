/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <ael-mous@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 14:04:50 by mait-jao          #+#    #+#             */
/*   Updated: 2022/12/08 22:44:01 by ael-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_len_num(int nbr)
{
	size_t	i;

	i = 0;
	if (nbr <= 0)
		i++;
	while (nbr != 0)
	{
		nbr = nbr / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		y;
	int		len;
	char	*str;

	len = ft_len_num(n);
	y = n;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	str = (char *) malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (n < 0)
		n *= -1;
	while ((--len) >= 0)
	{
		str[len] = (n % 10) + '0';
		n /= 10;
	}
	if (y < 0)
		str[++len] = '-';
	return (str);
}
