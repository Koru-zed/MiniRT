/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <ael-mous@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 05:53:48 by mait-jao          #+#    #+#             */
/*   Updated: 2022/12/08 22:44:31 by ael-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*plst;

	plst = lst;
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
	}
	return (lst);
}
