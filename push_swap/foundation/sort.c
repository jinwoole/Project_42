/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 16:04:18 by jinwoole          #+#    #+#             */
/*   Updated: 2022/04/13 23:50:46 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	scan_sorted(t_list *stack)
{
	const int	lstsize = ft_lstsize(stack);
	int			i;

	i = 1;
	while (lstsize > i)
	{
		if (ft_lstsel(stack, i)->content > ft_lstsel(stack, i + 1)->content)
			return (-1);
		i++;
	}
	return (1);
}

void	stack_sort(t_list *stack_a, t_list *stack_b)
{
	if (scan_sorted(stack_a) == 1)
		return ;
	if (ft_lstsize(stack_a) == 2)
		two_element_sort(stack_a);
	if (ft_lstsize(stack_a) == 3)
		three_element_sort(stack_a);
	if (ft_lstsize(stack_a) == 4)
		four_sort(stack_a, stack_b);
	if (ft_lstsize(stack_a) == 5)
		five_sort(stack_a, stack_b);
	if (ft_lstsize(stack_a) > 5)
	{
		indexing(stack_a);
		quick_sort(stack_a, stack_b);
	}
}
