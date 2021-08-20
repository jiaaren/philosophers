/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 18:47:36 by jkhong            #+#    #+#             */
/*   Updated: 2021/08/20 23:05:40 by jkhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libphilo_bonus.h"

static t_globals	g_args;

int main(void)
{
	int		*child_pid;
	int		num = 20;
	t_sems	sem;
	t_philo	philo;

	printf("\n");
	initialise_philo(&philo);
	unlink_sems();
	initialise_sem_main(0, &sem.start, SEM_START);
	child_pid = initialise_process(num, &philo);
	if (child_pid == NULL)
	{
		sem_wait(sem.start);
		sem_close(sem.start);
		// run child process
		printf("%li I am child %i!\n", givetime(), philo.philo_num);
	}
	else
	{
		for (int i = 0; i < num; i++)
			printf("%i\n", child_pid[i]);
		// initialise other semaphores
		for (int i = 0; i < num; i++)
			sem_post(sem.start);
		wait_children(num, child_pid);
		free(child_pid);
		sem_close(sem.start);
		// run parent process
	}
	return (0);
}
