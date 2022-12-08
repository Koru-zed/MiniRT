/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <ael-mous@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:22:02 by mait-jao          #+#    #+#             */
/*   Updated: 2022/12/08 22:44:17 by ael-mous         ###   ########.fr       */
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
