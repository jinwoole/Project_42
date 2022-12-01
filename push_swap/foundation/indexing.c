/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indexing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 12:07:58 by jinwoole          #+#    #+#             */
/*   Updated: 2022/04/10 15:59:47 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	indexing(t_list *stack)
{
	t_list	*indexed;
	int		lstsize;
	int		i;
	int		j;

	lstsize = ft_lstsize(stack);
	indexed = copy_stack(stack);
	sort_bubble(indexed);
	i = 1;
	while (lstsize)
	{
		j = 1;
		while (j <= ft_lstsize(indexed))
		{
			if (ft_lstsel(stack, i)->content == ft_lstsel(indexed, j)->content)
			{
				ft_lstsel(stack, i)->content = j;
				break ;
			}
			j++;
		}
		i++;
		lstsize--;
	}
	ft_lstfree(indexed);
}
/* i -> index of the original stack  j -> index of the sorted stack */