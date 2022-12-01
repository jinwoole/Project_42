/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_quick_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 12:41:44 by jinwoole          #+#    #+#             */
/*   Updated: 2022/04/11 22:04:47 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	chunk_select(t_list *stack)
{
	int	chunk;

	if (ft_lstsize(stack) <= 10)
		chunk = 9;
	else if (ft_lstsize(stack) <= 100)
		chunk = 20;
	else if (ft_lstsize(stack) <= 500)
		chunk = 25;
	else if (ft_lstsize(stack) <= 1000)
		chunk = 40;
	else if (ft_lstsize(stack) <= 5000)
		chunk = 125;
	else
		chunk = ft_lstsize(stack) / 10;
	return (chunk);
}

void	push_to_b(t_list *stack_a, t_list *stack_b)
{
	int	num;
	int	chunk;
	int	top;

	num = 1;
	chunk = chunk_select(stack_a);
	while (ft_lstsize(stack_a))
	{
		top = ft_lstsel(stack_a, 1)->content;
		if (top <= num)
		{
			pb(stack_a, stack_b);
			num++;
		}
		else if (num < top && top <= num + chunk)
		{
			pb(stack_a, stack_b);
			rb(stack_b);
			num++;
		}
		else if (num + chunk < top)
			ra(stack_a);
	}
}

int	biggest_value(t_list *stack)
{
	int	lstsize;
	int	i;
	int	biggest;

	lstsize = ft_lstsize(stack);
	biggest = ft_lstsel(stack, 1)->content;
	i = 2;
	while (lstsize - 1)
	{
		if (ft_lstsel(stack, i)->content > biggest)
		{
			biggest = ft_lstsel(stack, i)->content;
		}
		i++;
		lstsize--;
	}
	return (biggest);
}

void	push_to_a(t_list *stack_a, t_list *stack_b)
{
	int	biggest;
	int	i;

	biggest = biggest_value(stack_b);
	i = 1;
	while (biggest != ft_lstsel(stack_b, i)->content)
		i++;
	while (ft_lstsel(stack_b, 1)->content != biggest)
	{
		if (i <= ft_lstsize(stack_b) / 2)
			rb(stack_b);
		else
			rrb(stack_b);
	}
	pa(stack_a, stack_b);
}

void	quick_sort(t_list *stack_a, t_list *stack_b)
{
	push_to_b(stack_a, stack_b);
	while (ft_lstsize(stack_b))
		push_to_a(stack_a, stack_b);
}
