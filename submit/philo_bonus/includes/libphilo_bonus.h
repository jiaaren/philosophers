/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libphilo_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 18:48:15 by jkhong            #+#    #+#             */
/*   Updated: 2021/08/20 23:17:56 by jkhong           ###   ########.fr       */
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

typedef struct s_globals {
	int		philo_amount;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		times_philo_eat;
}				t_globals;

typedef	struct s_sems {
	sem_t	*forks;
	sem_t	*start;
	sem_t	*died;
	sem_t	*tummy;
}				t_sems;

typedef struct s_philo {
	int				philo_num;
	unsigned long	last_eat_time;
	int				times_eaten;
}				t_philo;

int		*initialise_process(int p_num, t_philo *philo);
void	wait_children(int p_num, int *child_pid);
void	initialise_philo(t_philo *philo);

unsigned long	givetime(void);

bool	initialise_sem_main(int p_num, sem_t **sem, char *sem_name);
bool	initialise_sem_philo(sem_t **sem, char *sem_name);
void	unlink_sems(void);
void	initialise_start_died_tummy(int p_num, t_sems *sems);
void	close_all_sems(t_sems *sems);

#endif