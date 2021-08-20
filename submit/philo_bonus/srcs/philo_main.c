/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 18:47:36 by jkhong            #+#    #+#             */
/*   Updated: 2021/08/20 23:23:05 by jkhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libphilo_bonus.h"

static t_globals	g_args;
static t_philo		g_philo;

int main(void)
{
	int		*child_pid;
	int		num = 20;
	t_sems	sems;

	initialise_philo(&g_philo);
	unlink_sems();
	initialise_sem_main(0, &sems.start, SEM_START);
	child_pid = initialise_process(num, &g_philo);
	if (child_pid == NULL)
	{
		sem_wait(sems.start);
		sem_close(sems.start);
		// run child process
		printf("%li I am child %i!\n", givetime(), g_philo.philo_num);
	}
	else
	{
		initialise_start_died_tummy(num, &sems);
		for (int i = 0; i < num; i++)
			sem_post(sems.start);
		wait_children(num, child_pid);
		free(child_pid);
		// run parent process
		close_all_sems(&sems);
	}
	return (0);
}
