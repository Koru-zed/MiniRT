/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <ael-mous@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:00:58 by mait-jao          #+#    #+#             */
/*   Updated: 2022/12/08 22:44:06 by ael-mous         ###   ########.fr       */
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
