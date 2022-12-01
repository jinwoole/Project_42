/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 17:19:38 by jinwoole          #+#    #+#             */
/*   Updated: 2022/03/26 16:27:17 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static void	ft_lstdel_next(t_list *lst)
{
	t_list	*target_node;

	target_node = lst->next;
	if (lst == 0)
		return ;
	lst->next = target_node->next;
	target_node->content = NULL;
	free(target_node);
}

void	ft_lstdel(t_list *lst, int index)
{
	int		lstsize;

	lstsize = ft_lstsize(lst);
	if (index > lstsize)
	{
		ft_printf("<ft_lstadd : index too  big! Max is %d.>\n", lstsize);
		return ;
	}
	if (index <= 0)
	{
		ft_printf("%s\n", "<ft_lstadd : Index starts at 1.>");
		return ;
	}
	ft_lstdel_next(ft_lstselect(lst, index - 1));
}
