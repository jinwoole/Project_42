/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 14:01:50 by jinwoole          #+#    #+#             */
/*   Updated: 2022/03/26 13:09:00 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_lstadd(t_list *lst, t_list *new, int index)
{
	int		lstsize;
	t_list	*element;

	lstsize = ft_lstsize(lst);
	if (lst == 0 || new == 0)
		return ;
	if (index > lstsize + 1)
	{
		ft_printf("<ft_lstadd : index too  big! Max is %d.>\n", lstsize + 1);
		free(new);
		return ;
	}
	if (index <= 0)
	{
		ft_printf("%s\n", "Index starts at 1, check github");
		free(new);
		return ;
	}
	element = ft_lstselect(lst, index - 1);
	new->next = element->next;
	element->next = new;
}
