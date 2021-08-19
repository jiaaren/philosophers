/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libphilo.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 17:51:50 by jkhong            #+#    #+#             */
/*   Updated: 2021/08/19 22:17:55 by jkhong           ###   ########.fr       */
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

typedef struct s_globals {
	bool	simulate;
	bool	ate_enough;
	int		philo_amount;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		times_philo_eat;
}				t_globals;

typedef struct s_philo {
	int				philo_num;
	unsigned long	last_eat_time;
	int				times_eaten;
	int				fork_one;
	int				fork_two;
}				t_philo;

void			initialise_philo(int p_num, t_philo **philo);
void			initialise_mutex(int p_num, pthread_mutex_t **forks);
void			create_thread(int p_num, pthread_t **thread,
					t_philo *philo, void *(f)(void *));
void			join_and_free_th(int p_num, pthread_t *th_cycle,
					pthread_t *th_death);
void			free_mutex_fork_philo(int p_num,
					pthread_mutex_t *forks, t_philo *philo);
unsigned long	givetime(void);
bool			initialise_globals(int params, char *args[],
					t_globals	*g_args);
void			end_cycle(t_globals *g_args);

#endif
