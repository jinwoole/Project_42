/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 15:50:39 by jinwoole          #+#    #+#             */
/*   Updated: 2022/04/13 23:28:50 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	ft_lstfree(t_list *lst)
{
	t_list	*tmp;
	t_list	*next;

	if (lst)
	{
		tmp = lst->next;
		while (tmp)
		{
			next = tmp->next;
			free(tmp);
			tmp = next;
		}
		free(lst);
	}
}
