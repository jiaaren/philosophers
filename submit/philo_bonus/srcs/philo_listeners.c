/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_listeners.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 02:11:48 by jkhong            #+#    #+#             */
/*   Updated: 2021/08/21 02:25:15 by jkhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libphilo_bonus.h"

// void	*hear_death(void *arg)
// {
// 	t_sems	sems;
// 	int		i;

// 	i = 0;
// 	sems = *(t_sems *)arg;
// 	sem_wait(sems.died);
// 	while (i < sems.philo_amount)
// 		sem_wait(sems.)
// 	return (NULL);
// }