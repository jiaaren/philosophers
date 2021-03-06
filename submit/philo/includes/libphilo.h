/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libphilo.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 17:51:50 by jkhong            #+#    #+#             */
/*   Updated: 2021/08/26 12:04:41 by jkhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBPHILO_H
# define LIBPHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_globals {
	bool	simulate;
	bool	ate_enough;
	int		tummies_filled;
	int		philo_amount;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		times_philo_eat;
}				t_globals;

typedef struct s_philo {
	int		philo_num;
	size_t	last_eat_time;
	int		times_eaten;
	int		fork_one;
	int		fork_two;
}				t_philo;

void	initialise_philo(int p_num, t_philo **philo);
void	initialise_mutex(int p_num, pthread_mutex_t **forks,
			pthread_mutex_t *seq);
void	create_thread(int p_num, pthread_t **thread,
			t_philo *philo, void *(f)(void *));
void	join_and_free_th(int p_num, pthread_t *th_cycle,
			pthread_t *th_death);
void	free_mutex_fork_philo(int p_num, pthread_mutex_t *forks,
			pthread_mutex_t *seq, t_philo *philo);
size_t	givetime(void);
bool	initialise_globals(int params, char *args[],
			t_globals	*g_args);
void	end_cycle(t_globals *g_args, t_philo *philo,
			pthread_mutex_t *forks);
void	ft_usleep(unsigned int n);

#endif
