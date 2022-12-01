/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <jinwoole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 15:23:42 by jinwoole          #+#    #+#             */
/*   Updated: 2022/04/02 16:49:02 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	error_exit(void)
{
	ft_putendl_fd("Error", 2);
	exit(-1);
}

long	ft_atoi_int(const char *str)
{
	long	num;
	long	i;
	long	n;
	long	result;

	n = 1;
	i = 0;
	num = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\f'
		|| str[i] == '\r' || str[i] == '\n' || str[i] == '\v')
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			n = -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	result = n * num;
	if (result > 2147483647 || result < -2147483648)
		error_exit();
	return (result);
}

void	is_num(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < 48 || argv[i][j] > 57)
			{
				if (ft_atoi_int(argv[i]) >= 0)
					error_exit();
				else
				{
					if (argv[i][0] != '-')
						error_exit();
				}
			}
			j++;
		}
		i++;
	}
}

void	is_dup(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = i + 1;
		while (argv[j])
		{
			if (ft_atoi_int(argv[i]) == ft_atoi_int(argv[j]))
				error_exit();
			j++;
		}
		i++;
	}
}

void	scan_error(char **argv)
{
	is_num(argv);
	is_dup(argv);
}
