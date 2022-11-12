/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_category_is.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-jao <mait-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 22:19:24 by mait-jao          #+#    #+#             */
/*   Updated: 2022/11/12 22:32:29 by mait-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	category_is_char(t_data *box)
{
	box->sum += pf_putchar((char)va_arg(box->list, int));
}

void	category_is_string(t_data *box)
{
	box->sum += pf_putstr((char *)va_arg(box->list, char *));
}

void	category_is_decint(t_data *box)
{
	box->sum += pf_putnbr(va_arg(box->list, int));
}

void	category_is_modulo(t_data *box)
{
	box->sum += (write(1, "%", 1));
}
