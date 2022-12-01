/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 14:01:50 by jinwoole          #+#    #+#             */
/*   Updated: 2022/04/13 23:34:23 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	ft_lstadd(t_list *lst, t_list *new, int index)
{
	int		lstsize;
	t_list	*element;

	lstsize = ft_lstsize(lst);
	if (lst == 0 || new == 0)
		return ;
	if (index > lstsize + 1)
	{
		free(new);
		return ;
	}
	if (index <= 0)
	{
		free(new);
		return ;
	}
	element = ft_lstsel(lst, index - 1);
	new->next = element->next;
	element->next = new;
}
