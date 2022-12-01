/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 23:46:24 by sesim             #+#    #+#             */
/*   Updated: 2022/08/12 00:04:22 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_free(void *src)
{
	if (src)
	{
		free(src);
		src = 0;
	}
}

void	clear_array(char **str, int flag)
{
	int	i;

	i = -1;
	if (!str)
		return ;
	while (str[++i])
		ft_free(str[i]);
	if (flag == 2)
	{
		ft_free(str);
		str = 0;
	}
}

void	clear_list(t_list **head)
{
	t_list	*tmp;

	if (!*head)
		return ;
	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp);
	}
	*head = 0;
}

void	clear_shell(t_shell *shell)
{
	int	i;
	int	k;

	i = -1;
	while (++i < shell->cp_pros->nbr_procs)
	{
		ft_free(shell->cp_pros->fd[i]);
		k = -1;
		while (++k < shell->cp_pros->child[i].infile_nbr)
			ft_free(shell->cp_pros->child[i].infile[k].file_name);
		k = -1;
		while (++k < shell->cp_pros->child[i].outfile_nbr)
			ft_free(shell->cp_pros->child[i].outfile[k].file_name);
		ft_free(shell->cp_pros->child[i].outfile);
		ft_free(shell->cp_pros->child[i].infile);
		ft_free(shell->cp_pros->child[i].cmd_group);
		clear_array(shell->cp_pros->child[i].cmd_split, 2);
	}
	ft_free(shell->cp_pros->pid);
	ft_free(shell->cp_pros->fd[i]);
	ft_free(shell->cp_pros->fd);
	ft_free(shell->cp_pros->child);
	clear_array(shell->cp_pros->orders, 2);
	ft_memset(shell->cp_pros, 0, sizeof(t_pros));
}
