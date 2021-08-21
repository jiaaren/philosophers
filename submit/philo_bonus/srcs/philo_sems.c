/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sems.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 22:52:45 by jkhong            #+#    #+#             */
/*   Updated: 2021/08/21 15:43:12 by jkhong           ###   ########.fr       */
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
	Start & end - initialise to 0
*/
void	initialise_all_sems(int p_num, t_sems *sems)
{
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_START);
	sem_unlink(SEM_END);
	sems->philo_amount = p_num;
	initialise_sem_main(p_num, &(sems->forks), SEM_FORKS);
	initialise_sem_main(0, &(sems->start), SEM_START);
	initialise_sem_main(0, &(sems->end), SEM_END);
}

void	close_all_sems(t_sems *sems)
{
	sem_close(sems->forks);
	sem_close(sems->start);
	sem_close(sems->end);
}

void	commence_cycle(sem_t *start, int p_num)
{
	int	i;

	i = 0;
	while (i++ < p_num)
		sem_post(start);
}
