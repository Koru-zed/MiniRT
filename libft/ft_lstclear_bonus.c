/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-jao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:22:02 by mait-jao          #+#    #+#             */
/*   Updated: 2021/11/22 14:54:50 by mait-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*dlst;

	if (lst)
	{
		while (*lst)
		{
			dlst = (*lst)->next;
			del((*lst)->content);
			free(*lst);
			*lst = dlst;
		}
	}
}
