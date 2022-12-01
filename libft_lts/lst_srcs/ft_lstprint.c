/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 09:09:38 by jinwoole          #+#    #+#             */
/*   Updated: 2022/03/26 14:22:48 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_lstprint(t_list *lst)
{
	if (lst == 0)
		return ;
	lst = lst->next;
	while (lst)
	{
		ft_printf("%d ", lst->content);
		lst = lst->next;
	}
}
