/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sems.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 22:52:45 by jkhong            #+#    #+#             */
/*   Updated: 2021/08/20 23:17:40 by jkhong           ###   ########.fr       */
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

void	unlink_sems(void)
{
	unlink(SEM_FORKS);
	unlink(SEM_START);
	unlink(SEM_DIED);
	unlink(SEM_TUMMY);
}

void	close_all_sems(t_sems *sems)
{
	sem_close(sems->forks);
	sem_close(sems->start);
	sem_close(sems->died);
	sem_close(sems->tummy);
}

/*
	Died and tummy - initialise to 0
*/
void	initialise_start_died_tummy(int p_num, t_sems *sems)
{
	initialise_sem_main(p_num, &(sems->forks), SEM_FORKS);
	initialise_sem_main(0, &(sems->died), SEM_DIED);
	initialise_sem_main(0, &(sems->tummy), SEM_TUMMY);
}