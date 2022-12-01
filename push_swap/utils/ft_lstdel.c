/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 17:19:38 by jinwoole          #+#    #+#             */
/*   Updated: 2022/04/13 23:34:15 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static void	ft_lstdel_next(t_list *lst)
{
	t_list	*target_node;

	target_node = lst->next;
	if (lst == 0)
		return ;
	lst->next = target_node->next;
	target_node->content = 0;
	free(target_node);
}

void	ft_lstdel(t_list *lst, int index)
{
	int		lstsize;

	lstsize = ft_lstsize(lst);
	if (index > lstsize)
		return ;
	if (index <= 0)
		return ;
	ft_lstdel_next(ft_lstsel(lst, index - 1));
}
