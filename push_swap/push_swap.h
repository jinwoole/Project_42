/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 23:12:00 by jinwoole          #+#    #+#             */
/*   Updated: 2022/04/13 23:36:10 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "stdlib.h"
# include "unistd.h"

typedef struct s_list
{
	int				content;
	struct s_list	*next;
}	t_list;

void	ft_push(t_list *out_list, t_list *in_list);
void	ft_swap(t_list *stack);
void	ft_rotate(t_list *stack);
void	ft_reverse_rotate(t_list *stack);
void	sa(t_list *stack_a);
void	sb(t_list *stack_b);
void	ss(t_list *stack_a, t_list *stack_b);
void	pa(t_list *stack_a, t_list *stack_b);
void	pb(t_list *stack_a, t_list *stack_b);
void	ra(t_list *stack_a);
void	rb(t_list *stack_b);
void	rr(t_list *stack_a, t_list *stack_b);
void	rra(t_list *stack_a);
void	rrb(t_list *stack_b);
void	rrb(t_list *stack_b);
void	stack_sort(t_list *stack_a, t_list *stack_b);
void	scan_error(char **argv);
int		scan_sorted(t_list *stack_a);
void	two_element_sort(t_list *stack_a);
void	three_element_sort(t_list *stack_a);
void	four_sort(t_list *stack_a, t_list *stack_b);
void	five_sort(t_list *stack_a, t_list *stack_b);
void	quick_sort(t_list *stack_a, t_list *stack_b);
t_list	*copy_stack(t_list *stack);
void	sort_bubble(t_list *copy);
void	indexing(t_list *stack);
int		ft_atoi(const char *str);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd(t_list *lst, t_list *new, int index);
void	ft_lstdel(t_list *lst, int index);
void	ft_lstfree(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(int content);
t_list	*ft_lstsel(t_list *lst, int index);
int		ft_lstsize(t_list *lst);
void	ft_putendl_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);

#endif