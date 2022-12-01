/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:13:54 by jinwoole          #+#    #+#             */
/*   Updated: 2022/06/23 14:36:57 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

static void	handler(int sig)
{
	static int	received = 0;

	if (sig == SIGUSR1)
		++received;
	else
	{
		ft_putnbr_fd(received, 1);
		ft_putchar_fd('\n', 1);
		exit(0);
	}
}

static void	roll_back(int pid)
{
	if (kill(pid, SIGUSR1) == -1)
		error_exit("Signal failed");
	usleep(100);
}

static void	messanger(int pid, char *str)
{
	int		i;
	char	c;

	while (*str)
	{
		i = 8;
		c = *str++;
		while (i--)
		{
			if (c >> i & 1)
			{
				if (kill(pid, SIGUSR2) == -1)
					error_exit("Signal failed");
			}
			else
			{
				if (kill(pid, SIGUSR1) == -1)
					error_exit("Signal failed");
			}
			usleep(100);
		}
	}
	i = 8;
	while (i--)
		roll_back(pid);
}

void	error_check(int argc, char **argv)
{
	int	i;

	if (argc != 3 || !ft_strlen(argv[2]))
		error_exit("invalid input");
	i = 0;
	while (argv[1][i])
	{
		if (ft_isdigit(argv[1][i]) == 0)
			error_exit("not num pid");
		i++;
	}
	if ((ft_atoi(argv[1]) > 99999) || (ft_atoi(argv[1]) < 100))
		error_exit("pid range error");
}

int	main(int argc, char **argv)
{
	error_check(argc, argv);
	ft_putstr_fd("Sent    : ", 1);
	ft_putnbr_fd(ft_strlen(argv[2]), 1);
	ft_putchar_fd('\n', 1);
	ft_putstr_fd("Received: ", 1);
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	messanger(ft_atoi(argv[1]), argv[2]);
	while (1)
		pause();
	return (0);
}
