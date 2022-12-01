/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 16:00:22 by jinwoole          #+#    #+#             */
/*   Updated: 2022/07/28 14:20:00 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *args)
{
	t_philo	*philos;

	philos = (t_philo *)args;
	while (1)
	{
		if (death_monitor(philos) == 1)
			return (0);
		if (philos->data->num_eat != -1)
		{
			if (eat_monitor(philos) == 1)
				return (0);
		}
	}
	return (0);
}

void	philo_start(t_philo *philos)
{
	int	i;

	i = 0;
	philos->data->start_time = get_time();
	while (i < philos->data->philo_num)
	{
		(philos + i)->eaten_time = get_time();
		if (pthread_create(&(philos + i)->thread, NULL, &routine, philos + i))
			error_exit("thread create failed");
		pthread_detach((philos + i)->thread);
		usleep(50);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_philo	*philos;

	if (argc < 5 || argc > 6)
		return (error_exit("Put 5 or 6 arguments"));
	if (init_philos(&philos, argc, argv) == -1)
		return (0);
	philo_start(philos);
	monitor(philos);
	let_them_free(philos);
	return (0);
}
