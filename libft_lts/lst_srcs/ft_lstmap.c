/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 13:10:04 by jinwoole          #+#    #+#             */
/*   Updated: 2022/03/20 15:54:37 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*result;
	t_list	*tmp;

	if (lst == 0 || f == 0)
		return (0);
	result = 0;
	while (lst)
	{
		tmp = ft_lstnew((*f)(lst->content));
		if (tmp == 0)
		{
			ft_lstclear(&result, del);
			return (0);
		}
		ft_lstadd_back(&result, tmp);
		tmp = tmp->next;
		lst = lst->next;
	}
	return (result);
}
