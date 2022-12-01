/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 11:41:56 by jinwoole          #+#    #+#             */
/*   Updated: 2022/04/05 11:03:17 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

t_list	*ft_lstsel(t_list *lst, int index)
{
	int	lstsize;

	lstsize = ft_lstsize(lst);
	if (index < 0)
	{
		return (0);
	}
	if (index > lstsize)
	{
		return (0);
	}
	while (index)
	{
		lst = lst->next;
		index--;
	}
	return (lst);
}
