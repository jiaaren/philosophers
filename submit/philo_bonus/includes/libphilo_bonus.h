/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libphilo_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 18:48:15 by jkhong            #+#    #+#             */
/*   Updated: 2021/08/21 21:31:49 by jkhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBPHILO_BONUS_H
# define LIBPHILO_BONUS_H

// headers for semaphores and constants
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
// threads
# include <pthread.h>
// malloc
# include <stdlib.h>
// printf
# include <stdio.h>
// sleep
# include <unistd.h>
// fork
# include <sys/types.h>
# include <stdbool.h>
// waitpid
# include <sys/wait.h>
// timeval
# include <sys/time.h>
// for INTMAX
# include <limits.h>

# define SEM_FORKS "/forks"
# define SEM_START "/start"
# define SEM_END "/end"

typedef struct s_globals {
	bool	simulate;
	int		philo_amount;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		threads_ended;
}				t_globals;

typedef struct s_sems {
	int		philo_amount;
	sem_t	*forks;
	sem_t	*start;
	sem_t	*end;
}				t_sems;

typedef struct s_philo {
	int			philo_num;
	size_t		last_eat_time;
	int			times_eaten;
	pthread_t	th_death;
	pthread_t	th_hear_parent;
}				t_philo;

// initialisations from main
bool	initialise_globals(int params, char *args[],
			t_globals	*g_args);
void	philo_main(t_globals args);

// initialisations from philo_main
void	initialise_philo(t_philo *philo);
int		*initialise_process(int p_num, t_philo *philo,
			void *(death_cycle)(void *), void *(hear_one_death)(void *));
void	wait_children(int p_num, int *child_pid);

// utilities
size_t	givetime(void);
void	end_cycle(t_globals *g_args);
void	commence_cycle(sem_t *start, int p_num);

// semaphore utils
bool	initialise_sem_main(int p_num, sem_t **sem, char *sem_name);
bool	initialise_sem_philo(sem_t **sem, char *sem_name);
void	initialise_all_sems(int p_num, t_sems *sems);
void	close_all_sems(t_sems *sems);

void	ft_usleep(unsigned int n);

#endif