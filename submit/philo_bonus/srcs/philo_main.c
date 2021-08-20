/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 18:47:36 by jkhong            #+#    #+#             */
/*   Updated: 2021/08/20 21:03:29 by jkhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libphilo_bonus.h"

static t_globals	g_args;

int main(void)
{
	int	*child_pid;
	int num = 20;
	sem_t *sem_start;

	printf("\n");
	sem_unlink(SEM_START);
	initialise_sem_main(0, &sem_start, SEM_START);
	child_pid = initialise_process(num);
	if (child_pid == NULL)
	{
		sem_close(sem_start);
		initialise_sem_philo(&sem_start, SEM_START);
		sem_wait(sem_start);
		printf("%li I am a child!\n", givetime());
		sem_close(sem_start);
	}
	else
	{
		usleep(500000);
		for (int i = 0; i < num; i++)
			printf("%i\n", child_pid[i]);
		for (int i = 0; i < num; i++)
			sem_post(sem_start);
		wait_children(num, child_pid);
		free(child_pid);
		sem_close(sem_start);
	}
	return (0);
}
