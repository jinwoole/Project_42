/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 15:50:39 by jinwoole          #+#    #+#             */
/*   Updated: 2022/03/26 16:26:51 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

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
			tmp->content = NULL;
			free(tmp);
			tmp = next;
		}
		free(lst);
	}
}
