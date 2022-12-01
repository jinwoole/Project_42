/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   four_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 21:24:27 by jinwoole          #+#    #+#             */
/*   Updated: 2022/04/10 16:03:12 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	index_big(t_list *stack_a)
{
	int	biggest;
	int	i;
	int	j;
	int	r;

	i = 2;
	j = 3;
	r = 1;
	biggest = ft_lstsel(stack_a, 1)->content;
	while (j)
	{
		if (biggest < ft_lstsel(stack_a, i)->content)
		{
			r = i;
			biggest = ft_lstsel(stack_a, i)->content;
		}
		i++;
		j--;
	}
	return (r);
}

int	index_small(t_list *stack_a)
{
	int	smallest;
	int	i;
	int	j;
	int	r;

	i = 2;
	j = 3;
	r = 1;
	smallest = ft_lstsel(stack_a, 1)->content;
	while (j)
	{
		if (smallest > ft_lstsel(stack_a, i)->content)
		{
			r = i;
			smallest = ft_lstsel(stack_a, i)->content;
		}
		i++;
		j--;
	}
	return (r);
}

void	do_operation(t_list *stack_a, t_list *stack_b)
{
	int	first_content;
	int	second_content;

	first_content = ft_lstsel(stack_b, 1)->content;
	second_content = ft_lstsel(stack_b, 2)->content;
	if (first_content > second_content)
	{
		pa(stack_a, stack_b);
		ra(stack_a);
		pa(stack_a, stack_b);
	}
	else
	{
		rb(stack_b);
		pa(stack_a, stack_b);
		ra(stack_a);
		pa(stack_a, stack_b);
	}
}

void	four_sort(t_list *stack_a, t_list *stack_b)
{
	int		lstsize;
	int		biggest;
	int		smallest;
	int		i;

	i = 1;
	lstsize = 4;
	biggest = index_big(stack_a);
	smallest = index_small(stack_a);
	while (lstsize)
	{
		if (i == biggest || i == smallest)
			pb(stack_a, stack_b);
		else
			ra(stack_a);
		i++;
		lstsize--;
	}
	two_element_sort(stack_a);
	do_operation(stack_a, stack_b);
}
