/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_initialise.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 18:51:44 by jkhong            #+#    #+#             */
/*   Updated: 2021/08/21 02:44:09 by jkhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libphilo_bonus.h"


void	wait_children(int p_num, int *child_pid)
{
	int i;

	i = 0;
	while (i < p_num)
		waitpid(child_pid[i++], NULL, 0);
}

void	initialise_philo(t_philo *philo)
{
	philo->philo_num = 0;
	philo->last_eat_time = 0;
	philo->times_eaten = 0;
}


