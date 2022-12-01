/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 21:28:52 by sesim             #+#    #+#             */
/*   Updated: 2022/08/12 00:12:49 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

int	g_sig_md;

# include "../libft/libft_src/libft.h"
# include <signal.h>

typedef struct s_file
{
	int		type;
	char	*file_name;
	char	**file_name_clean;
}	t_file;

typedef struct s_child
{
	t_file	*infile;
	t_file	*outfile;
	char	*cmd_group;
	char	**cmd_split;
	int		mom_builtin;
	int		idx;
	int		cmd_nbr;
	int		infile_nbr;
	int		outfile_nbr;
	int		index_in;
	int		index_out;
}	t_child;

typedef struct s_pros
{
	int		nbr_procs;
	int		**fd;
	char	**orders;
	pid_t	*pid;
	t_child	*child;
}	t_pros;

typedef	struct s_envs
{
	char	**env;
	char	**paths;
	char	**var_real;
	char	*home;
	int		nbr_var;
	t_list	*list_var_real;
	t_list	*list_env;
}	t_envs;

typedef struct s_shell
{
	int		check;
	int		builtin_status;
	int		status;
	char	*line;
	t_envs	*cp_envs;
	t_pros	*cp_pros;
}	t_shell;

/*     terminal_functions     */
int	create_terminal(t_shell *shell);

/*     signal functions     */
void	handler(int sig);

/*     error_functions     */
void	error_status(char *str, int errno);

/*     free functions     */
void	ft_free(void *src);
void	clear_array(char **str, int flag);
void	clear_list(t_list **head);
void	clear_shell(t_shell *shell);

#endif
