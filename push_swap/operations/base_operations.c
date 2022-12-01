/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 23:19:19 by jinwoole          #+#    #+#             */
/*   Updated: 2022/04/10 14:46:53 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	ft_push(t_list *out, t_list *in)
{
	if (ft_lstsize(out) <= 0)
		return ;
	ft_lstadd(in, ft_lstnew(ft_lstsel(out, 1)->content), 1);
	ft_lstdel(out, 1);
}

void	ft_swap(t_list *stack)
{
	t_list	*temp;
	t_list	*top;

	if (ft_lstsize(stack) <= 1)
		return ;
	temp = ft_lstnew(0);
	top = ft_lstsel(stack, 1);
	temp->content = top->content;
	top->content = ft_lstsel(stack, 2)->content;
	ft_lstsel(stack, 2)->content = temp->content;
	free(temp);
}

void	ft_rotate(t_list *stack)
{
	t_list	*moved;

	moved = ft_lstsel(stack, 1);
	ft_lstadd_back(&stack, ft_lstnew(moved->content));
	ft_lstdel(stack, 1);
}

void	ft_reverse_rotate(t_list *stack)
{
	t_list	*line_too_long;

	line_too_long = ft_lstnew(ft_lstlast(stack)->content);
	ft_lstadd(stack, line_too_long, 1);
	ft_lstdel(stack, ft_lstsize(stack));
}

void	ra(t_list *stack_a)
{
	if (ft_lstsize(stack_a) == 0)
		return ;
	ft_rotate(stack_a);
	ft_putendl_fd("ra", 1);
}
