/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstselect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <jinwoole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 11:41:56 by jinwoole          #+#    #+#             */
/*   Updated: 2022/03/24 17:39:10 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_list	*ft_lstselect(t_list *lst, int index)
{
	int	lstsize;

	lstsize = ft_lstsize(lst);
	if (index < 0)
	{
		ft_printf("%s\n", "Index cannot be -, rtn [0]");
		return (lst);
	}
	if (index > lstsize)
	{
		ft_printf("<ft_lstselect : Max index is %d. rtn [0]>", lstsize);
		write(1, "\n", 1);
		return (lst);
	}
	while (index)
	{
		lst = lst->next;
		index--;
	}
	return (lst);
}
