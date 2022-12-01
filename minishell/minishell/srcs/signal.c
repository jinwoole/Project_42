/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 00:05:15 by sesim             #+#    #+#             */
/*   Updated: 2022/08/12 00:12:17 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

void    handler(int sig)
{
	if (sig == SIGINT && g_sig_md == 1)
    {
        printf("\n");
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
	if (sig == SIGINT && g_sig_md == 4)
	{
		printf("\n");
		rl_on_new_line();
	}
	if (sig == SIGQUIT && g_sig_md == 4)
		ft_putendl_fd("Quit : 3", 1);
}
