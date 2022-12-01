/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:14:00 by jinwoole          #+#    #+#             */
/*   Updated: 2022/06/23 14:11:32 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	pid_check(pid_t client_pid, siginfo_t *info)
{
	if (client_pid != info->si_pid)
		error_exit("signal interrupted");
}

static void	action(int sig, siginfo_t *info, void *context)
{
	static int				i = 0;
	static pid_t			client_pid = 0;
	static unsigned char	c = 0;

	(void)context;
	client_pid = 0;
	if (!client_pid)
		client_pid = info->si_pid;
	pid_check(client_pid, info);
	c |= (sig == SIGUSR2);
	if (++i == 8)
	{
		i = 0;
		if (!c)
		{
			if (kill(client_pid, SIGUSR2) == -1)
				error_exit("signal failed");
			return ;
		}
		ft_putchar_fd(c, 1);
		c = 0;
		kill(client_pid, SIGUSR1);
	}
	else
		c <<= 1;
}

int	main(void)
{
	struct sigaction	s_sigaction;

	ft_putstr_fd("Server PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	s_sigaction.sa_sigaction = action;
	s_sigaction.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &s_sigaction, 0) == -1)
		error_exit("signal failed");
	if (sigaction(SIGUSR2, &s_sigaction, 0) == -1)
		error_exit("signal failed");
	while (1)
		pause();
	return (0);
}
