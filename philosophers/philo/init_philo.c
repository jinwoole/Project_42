/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 11:12:51 by jinwoole          #+#    #+#             */
/*   Updated: 2022/07/27 15:49:25 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	find_argv(const char *str)
{
	long	n;
	int		max_int;

	max_int = 2147483647;
	while (*str == ' ' || *str == '\f' || *str == '\n' || \
			*str == '\r' || *str == '\t' || *str == '\v')
		str++;
	n = 0;
	if (*str == '-')
		return (-1);
	if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		n = n * 10 + *str - '0';
		if (n > max_int)
			return (-1);
		str++;
	}
	if (*str != '\0')
		return (-1);
	return ((int)n);
}

static int	init_data(t_sim **data, int argc, char **argv)
{
	t_sim	*tmp;

	tmp = (t_sim *)malloc(sizeof(t_sim));
	if (!tmp)
		return (error_exit("Malloc failed"));
	tmp->philo_num = find_argv(argv[1]);
	tmp->forks_num = tmp->philo_num;
	tmp->time_die = find_argv(argv[2]);
	tmp->time_to_eat = find_argv(argv[3]);
	tmp->time_to_sleep = find_argv(argv[4]);
	if (tmp->philo_num < 1 || tmp->time_die <= -1 || tmp->time_to_eat <= -1 || \
		tmp->time_to_sleep <= -1)
		return (error_exit("Put right arguments"));
	tmp->num_eat = -1;
	if (argc == 6)
	{
		tmp->num_eat = find_argv(argv[5]);
		if (tmp->num_eat <= 0)
			return (error_exit("Put right arguments"));
	}
	tmp->stop = 0;
	*data = tmp;
	return (0);
}

static int	init_fork(t_sim *data)
{
	int	i;

	data->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
					* data->forks_num);
	if (!data->fork)
		return (error_exit("Malloc failed"));
	i = -1;
	while (++i < data->forks_num)
	{
		if (pthread_mutex_init(data->fork + i, NULL))
			return (error_exit("mutex init failed"));
	}
	return (0);
}

static void	init_philo(t_philo *philo, int i, \
						t_sim *data, pthread_mutex_t *forks)
{
	philo->index = i + 1;
	philo->eat_count = 0;
	philo->eaten_time = 0;
	philo->data = data;
	if (i == 0)
	{
		philo->left_fork = forks + data->philo_num - 1;
		philo->right_fork = forks + i;
	}
	else
	{
		philo->left_fork = forks + i - 1;
		philo->right_fork = forks + i;
	}
}

int	init_philos(t_philo **philos, int argc, char **argv)
{
	t_sim	*data;
	t_philo	*tmp;
	int		i;

	if (init_data(&data, argc, argv) == -1)
		return (-1);
	if (pthread_mutex_init(&data->print, NULL))
		return (error_exit("mutex init fail"));
	if (pthread_mutex_init(&data->s_locker, NULL))
		return (error_exit("mutex init fail"));
	if (pthread_mutex_init(&data->p_locker, NULL))
		return (error_exit("mutex init fail"));
	if (init_fork(data) == -1)
		return (-1);
	tmp = (t_philo *)malloc(sizeof(t_philo) * data->philo_num);
	if (!tmp)
		return (error_exit("Malloc failed"));
	i = -1;
	while (++i < data->philo_num)
		init_philo(tmp + i, i, data, data->fork);
	*philos = tmp;
	return (0);
}
