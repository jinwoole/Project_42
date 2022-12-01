/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   two_three_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 10:17:49 by jinwoole          #+#    #+#             */
/*   Updated: 2022/04/10 15:11:15 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	two_element_sort(t_list *stack_a)
{
	int	first_content;
	int	second_content;

	first_content = ft_lstsel(stack_a, 1)->content;
	second_content = ft_lstsel(stack_a, 2)->content;
	if (first_content > second_content)
		sa(stack_a);
}

void	lazy_sort(int one, int two, int three, t_list *stack_a)
{
	if (one > two && one > three)
	{
		if (two > three)
		{
			sa(stack_a);
			rra(stack_a);
		}
		else
			ra(stack_a);
	}
	else if (two > one && two > three)
	{
		if (one > three)
			rra(stack_a);
		else
		{
			rra(stack_a);
			sa(stack_a);
		}
	}
	else if (three > one && three > two)
	{
		if (one > two)
			sa(stack_a);
	}
}

void	three_element_sort(t_list *stack_a)
{
	int	one;
	int	two;
	int	three;

	one = ft_lstsel(stack_a, 1)->content;
	two = ft_lstsel(stack_a, 2)->content;
	three = ft_lstsel(stack_a, 3)->content;
	lazy_sort(one, two, three, stack_a);
}
