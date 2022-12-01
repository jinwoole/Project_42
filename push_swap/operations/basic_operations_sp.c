/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_operations_sp.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:39:57 by jinwoole          #+#    #+#             */
/*   Updated: 2022/04/09 22:05:32 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	sa(t_list *stack_a)
{
	ft_swap(stack_a);
	ft_putendl_fd("sa", 1);
}

void	sb(t_list *stack_b)
{
	ft_swap(stack_b);
	ft_putendl_fd("sb", 1);
}

void	ss(t_list *stack_a, t_list *stack_b)
{
	ft_swap(stack_a);
	ft_swap(stack_b);
	ft_putendl_fd("ss", 1);
}

void	pa(t_list *stack_a, t_list *stack_b)
{
	ft_push(stack_b, stack_a);
	ft_putendl_fd("pa", 1);
}

void	pb(t_list *stack_a, t_list *stack_b)
{
	ft_push(stack_a, stack_b);
	ft_putendl_fd("pb", 1);
}
