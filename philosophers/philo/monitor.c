/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 14:18:43 by jinwoole          #+#    #+#             */
/*   Updated: 2022/07/28 14:22:25 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	raise_flag(t_philo *philos)
{
	pthread_mutex_lock(&philos->data->s_locker);
	philos->data->stop = 1;
	pthread_mutex_unlock(&philos->data->s_locker);
	pthread_mutex_unlock(&philos->data->p_locker);
}

int	eat_monitor(t_philo *philos)
{
	int		i;
	int		counter;

	i = -1;
	counter = 0;
	while (++i < philos->data->philo_num)
	{
		pthread_mutex_lock(&philos->data->p_locker);
		if (philos->data->stop == 1)
		{
			pthread_mutex_unlock(&philos->data->p_locker);
			return (1);
		}
		if (philos->data->num_eat != -1 && \
			(philos + i)->eat_count >= philos->data->num_eat)
			counter++;
		if (counter == philos->data->philo_num)
		{
			raise_flag(philos);
			return (1);
		}
		pthread_mutex_unlock(&philos->data->p_locker);
	}
	return (0);
}

int	death_monitor(t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < philos->data->philo_num)
	{
		pthread_mutex_lock(&philos->data->p_locker);
		if (get_time() - (philos + i)->eaten_time >= philos->data->time_die)
		{
			philo_print(philos + i, "died");
			pthread_mutex_lock(&philos->data->s_locker);
			philos->data->stop = 1;
			pthread_mutex_unlock(&philos->data->s_locker);
			pthread_mutex_unlock(&philos->data->p_locker);
			return (1);
		}
		if (philos->data->stop == 1)
		{
			pthread_mutex_unlock(&philos->data->p_locker);
			return (1);
		}
		pthread_mutex_unlock(&philos->data->p_locker);
	}
	return (0);
}
