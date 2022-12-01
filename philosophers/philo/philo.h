/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 16:09:19 by jinwoole          #+#    #+#             */
/*   Updated: 2022/07/28 14:22:15 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_sim
{
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
	pthread_mutex_t	s_locker;
	pthread_mutex_t	p_locker;
	pthread_t		check_monitor;
	pthread_t		death_monitor;
	int				philo_num;
	int				forks_num;
	int				time_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_eat;
	int				stop;
	long			start_time;
}		t_sim;

typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				index;
	int				eat_count;
	long			eaten_time;
	t_sim			*data;
}		t_philo;

int		init_philos(t_philo **philos, int argc, char **argv);
int		error_exit(char *str);
long	get_time(void);
void	ft_usleep(long time);
void	philo_print(t_philo *philo, char *str);
void	*routine(void *args);
void	let_them_free(t_philo *philos);
int		eat_monitor(t_philo *philos);
int		death_monitor(t_philo *philos);

#endif
