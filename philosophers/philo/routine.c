/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 19:17:58 by jinwoole          #+#    #+#             */
/*   Updated: 2022/07/28 14:14:50 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->s_locker);
	if (philo->data->stop == 1)
		return (1);
	pthread_mutex_unlock(&philo->data->s_locker);
	pthread_mutex_lock(philo->left_fork);
	philo_print(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	philo_print(philo, "has taken a fork");
	return (0);
}

int	eating(t_philo *philo)
{
	if (philo->data->stop == 1)
		return (1);
	pthread_mutex_lock(&philo->data->p_locker);
	philo->eaten_time = get_time();
	pthread_mutex_unlock(&philo->data->p_locker);
	philo_print(philo, "is eating");
	pthread_mutex_lock(&philo->data->p_locker);
	pthread_mutex_lock(&philo->data->s_locker);
	if (!philo->data->stop && philo->data->num_eat)
		philo->eat_count += 1;
	pthread_mutex_unlock(&philo->data->s_locker);
	pthread_mutex_unlock(&philo->data->p_locker);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (0);
}

int	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->s_locker);
	if (philo->data->stop == 1)
		return (1);
	pthread_mutex_unlock(&philo->data->s_locker);
	philo_print(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep);
	return (0);
}

int	thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->s_locker);
	if (philo->data->stop == 1)
		return (1);
	pthread_mutex_unlock(&philo->data->s_locker);
	philo_print(philo, "is thinking");
	return (0);
}

void	*routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (1)
	{
		if (take_fork(philo) == 1)
			return (0);
		if (eating(philo) == 1)
			return (0);
		if (sleeping(philo) == 1)
			return (0);
		if (thinking(philo) == 1)
			return (0);
		if (philo->data->stop == 1)
			return (0);
	}
	return (0);
}
