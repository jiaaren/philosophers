/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libphilo_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 18:48:15 by jkhong            #+#    #+#             */
/*   Updated: 2021/08/21 02:47:31 by jkhong           ###   ########.fr       */
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
# define SEM_DIED "/died"
# define SEM_TUMMY "/tummy"
# define SEM_END "/end"

typedef struct s_globals {
	bool	simulate;
	bool	ate_enough;
	int		philo_amount;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		times_philo_eat;
    int		threads_ended;
}				t_globals;

typedef	struct s_sems {
    int     philo_amount;
	sem_t	*forks;
	sem_t	*start;
	sem_t	*died;
	sem_t	*tummy;
    sem_t   *end;
}				t_sems;

typedef struct s_philo {
	int				philo_num;
	unsigned long	last_eat_time;
	int				times_eaten;
	union {
		pthread_t	th_death;
		pthread_t	th_hear_parent;
	} th1;
	union {
		pthread_t	th_hear_death;
		pthread_t	th_hear_child_ate;
	} th2;
}				t_philo;

// int		*initialise_process(int p_num, t_philo *philo, void *(f)(void *));
void	wait_children(int p_num, int *child_pid);
void	initialise_philo(t_philo *philo);

unsigned long	givetime(void);
void	end_cycle(t_globals *g_args);

bool	initialise_sem_main(int p_num, sem_t **sem, char *sem_name);
bool	initialise_sem_philo(sem_t **sem, char *sem_name);
void	unlink_sems(void);
void	initialise_all_sems(int p_num, t_sems *sems);
void	close_all_sems(t_sems *sems);

void	*hear_child_death(void *arg);
void	*hear_one_death(void *arg);

#endif