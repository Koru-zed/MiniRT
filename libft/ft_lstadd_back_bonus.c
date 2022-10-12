/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-jao <mait-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:00:58 by mait-jao          #+#    #+#             */
/*   Updated: 2022/10/12 10:35:11 by mait-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*plst;

	if (lst && new)
	{
		if (*lst)
		{
			plst = ft_lstlast(*lst);
			plst->next = new;
		}
		else
			*lst = new;
	}
}
