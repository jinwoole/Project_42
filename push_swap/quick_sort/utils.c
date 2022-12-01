/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pivot_select.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 16:30:56 by jinwoole          #+#    #+#             */
/*   Updated: 2022/04/11 21:48:25 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	biggest_index(t_list *stack)
{
	int	lstsize;
	int	i;
	int	biggest;
	int	index;

	lstsize = ft_lstsize(stack);
	biggest = ft_lstsel(stack, 1)->content;
	index = 1;
	i = 2;
	while (lstsize - 1)
	{
		if (ft_lstsel(stack, i)->content > biggest)
		{
			biggest = ft_lstsel(stack, i)->content;
			index = i;
		}
		i++;
		lstsize--;
	}
	return (index);
}

t_list	*copy_stack(t_list *stack)
{
	t_list	*temp;
	int		index;
	int		lstsize;

	lstsize = ft_lstsize(stack);
	temp = ft_lstnew(0);
	index = 1;
	while (lstsize)
	{
		ft_lstadd_back(&temp, ft_lstnew(ft_lstsel(stack, index)->content));
		index++;
		lstsize--;
	}
	return (temp);
}

void	sort_bubble(t_list *copy)
{
	int	temp;
	int	j_content;
	int	j_plus;
	int	i;
	int	j;

	i = 1;
	while (i < ft_lstsize(copy))
	{
		j = 1;
		while (j < ft_lstsize(copy))
		{
			j_content = ft_lstsel(copy, j)->content;
			j_plus = ft_lstsel(copy, j + 1)->content;
			if (j_content > ft_lstsel(copy, j + 1)->content)
			{
				temp = ft_lstsel(copy, j)->content;
				ft_lstsel(copy, j)->content = j_plus;
				ft_lstsel(copy, j + 1)->content = temp;
			}
			j++;
		}
		i++;
	}
}
