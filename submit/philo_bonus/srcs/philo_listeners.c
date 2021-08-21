/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_listeners.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 02:11:48 by jkhong            #+#    #+#             */
/*   Updated: 2021/08/21 10:51:27 by jkhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libphilo_bonus.h"

void	*hear_child_death(void *arg)
{
	t_sems	*sems;
	int		i;

	sems = (t_sems *)arg;
	i = 0;
	sem_wait(sems->died);
	while (i++ < sems->philo_amount)
		sem_post(sems->end);
	return (NULL);
}


