/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 09:00:35 by jinwoole          #+#    #+#             */
/*   Updated: 2022/07/28 14:17:39 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_exit(char *str)
{
	printf("%s\n", str);
	return (-1);
}

long	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	ft_usleep(long time)
{
	long	t;

	t = get_time();
	while (1)
	{
		if (get_time() - t >= time)
			break ;
		usleep(10);
	}
}

void	let_them_free(t_philo *philos)
{
	int	i;

	i = 0;
	sleep(1);
	while (i < philos->data->forks_num)
	{
		pthread_mutex_destroy(&philos->data->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&philos->data->print);
	pthread_mutex_destroy(&philos->data->s_locker);
	pthread_mutex_destroy(&philos->data->p_locker);
	free(philos->data->fork);
	free(philos->data);
	free(philos);
}

void	philo_print(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->print);
	pthread_mutex_lock(&philo->data->s_locker);
	if (philo->data->stop == 1)
	{
		pthread_mutex_unlock(&philo->data->s_locker);
		pthread_mutex_unlock(&philo->data->print);
		return ;
	}
	pthread_mutex_unlock(&philo->data->s_locker);
	printf("%ld %d %s\n", \
		get_time() - philo->data->start_time, philo->index, str);
	pthread_mutex_unlock(&philo->data->print);
}
