/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 23:30:44 by jinwoole          #+#    #+#             */
/*   Updated: 2022/04/12 15:25:13 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	push_swap(t_list *stack_a, t_list *stack_b, int argc, char **argv)
{
	int	i;
	int	argv_value;

	i = 1;
	while (argc > i)
	{
		argv_value = ft_atoi(argv[i]);
		ft_lstadd_back(&stack_a, ft_lstnew((argv_value)));
		i++;
	}
	stack_sort(stack_a, stack_b);
}

int	main(int argc, char **argv)
{
	t_list	*stack_a;
	t_list	*stack_b;

	if (argc < 2)
		exit(-1);
	scan_error(argv);
	stack_a = malloc(sizeof(t_list));
	stack_b = malloc(sizeof(t_list));
	push_swap(stack_a, stack_b, argc, argv);
	ft_lstfree(stack_a);
	ft_lstfree(stack_b);
	exit(0);
}
