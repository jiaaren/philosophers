/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libphilo_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 18:48:15 by jkhong            #+#    #+#             */
/*   Updated: 2021/08/20 21:00:38 by jkhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBPHILO_BONUS_H
# define LIBPHILO_BONUS_H

# define SEM_FORKS "/forks"
# define SEM_START "/start"

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

typedef struct s_globals {
	int		philo_amount;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		times_philo_eat;
}				t_globals;

int	*initialise_process(int p_num);
void	wait_children(int p_num, int *child_pid);
bool	initialise_sem_main(int p_num, sem_t **sem, char *sem_name);
bool	initialise_sem_philo(sem_t **sem, char *sem_name);

unsigned long	givetime(void);

#endif