/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_operations_r.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 18:02:55 by jinwoole          #+#    #+#             */
/*   Updated: 2022/04/11 21:10:22 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	rb(t_list *stack_b)
{
	ft_rotate(stack_b);
	ft_putendl_fd("rb", 1);
}
//'ra'is at 'base_operations.c'

void	rr(t_list *stack_a, t_list *stack_b)
{
	ft_rotate(stack_a);
	ft_rotate(stack_b);
	ft_putendl_fd("rr", 1);
}

void	rra(t_list *stack_a)
{
	if (ft_lstsize(stack_a) == 0)
		return ;
	ft_reverse_rotate(stack_a);
	ft_putendl_fd("rra", 1);
}

void	rrb(t_list *stack_b)
{
	if (ft_lstsize(stack_b) == 0)
		return ;
	ft_reverse_rotate(stack_b);
	ft_putendl_fd("rrb", 1);
}

void	rrr(t_list *stack_a, t_list *stack_b)
{
	ft_reverse_rotate(stack_a);
	ft_reverse_rotate(stack_b);
	ft_putendl_fd("rrr", 1);
}
