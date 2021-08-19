/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libphilo.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 17:51:50 by jkhong            #+#    #+#             */
/*   Updated: 2021/08/19 20:28:45 by jkhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef LIBPHILO_H
# define LIBPHILO_H

#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/time.h>

typedef struct  s_globals {
	int philo_amount;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int times_philo_eat;
	int threads_ended;
}               t_globals;

typedef struct  s_philo {
	int philo_num;
	unsigned long last_eat_time;
	int times_eaten;
	int fork_one;
	int fork_two;
}               t_philo;

void	initialise_philo(int p_num, t_philo **philo);
void	initialise_mutex(int p_num, pthread_mutex_t **forks);
void	free_threads(int p_num, pthread_t *thread,
		pthread_mutex_t *forks, t_philo *philo);

# endif
