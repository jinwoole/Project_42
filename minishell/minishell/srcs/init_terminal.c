/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_terminal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 23:37:01 by sesim             #+#    #+#             */
/*   Updated: 2022/08/12 00:16:29 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../libft/libft_src/libft.h"
#include <readline/readline.h>
#include <readline/history.h>

char	*get_line(t_shell *shell)
{
	if (shell->line && shell->line[0] != '\0')
	{
		ft_free(shell->line);
		shell->line = 0;
	}
	shell->line = readline("Minishell $");
	if (shell->line && shell->line[0] != '\0')
		add_history(shell->line);
	if (shell->line && !ft_strncmp(shell->line, "history -c", \
		ft_strlen("history -c")))
		rl_clear_history();
	return (shell->line);
}

int	create_terminal(t_shell *shell)
{
	g_sig_md = 1;
	shell->line = 0;
	rl_catch_signals = 0;
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	while(1)
	{
		shell->line = get_line(shell);
		if (!shell->line)
		{
			printf("exit");
			exit(0);
		}
		else if (shell->line[0] != '\0')
		{
			g_sig_md = 4;
			parser(shell);
			ft_free(shell->line);
			shell->line = 0;
			g_sig_md = 1;
		}
	}
	return (0);
}
