/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_initialise.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 18:51:44 by jkhong            #+#    #+#             */
/*   Updated: 2021/08/20 20:59:54 by jkhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libphilo_bonus.h"

bool	initialise_sem_main(int p_num, sem_t **sem, char *sem_name)
{
	*sem = sem_open(sem_name, O_CREAT, 0660, p_num);
	if (*sem == SEM_FAILED)
		return (false);
	return (true);
}

bool	initialise_sem_philo(sem_t **sem, char *sem_name)
{
	*sem = sem_open(sem_name, 0);
	if (*sem == SEM_FAILED)
		return (false);
	return (true);
}

/*
	Handle freeing of malloc locally within function
	free when pid == 0, and return NULL
	if parent, return int array
*/
int	*initialise_process(int p_num)
{
	int	*child_pid;
	int	pid;
	int	i;

	child_pid = malloc(sizeof(int) * p_num);
	i = 0;
	while (i < p_num)
	{
		pid = fork();
		if (pid == 0)
			break;
		child_pid[i] = pid;
		i++;
	}
	if (pid != 0)
		return (child_pid);
	free(child_pid);
	return (NULL);
}

void	wait_children(int p_num, int *child_pid)
{
	int i;

	i = 0;
	while (i < p_num)
		waitpid(child_pid[i++], NULL, 0);
}