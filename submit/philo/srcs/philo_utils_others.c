/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_others.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 21:00:04 by jkhong            #+#    #+#             */
/*   Updated: 2021/08/19 21:21:40 by jkhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libphilo.h"

unsigned long	givetime(void)
{
	struct timeval	_timeval;

	gettimeofday(&_timeval, NULL);
	return ((_timeval.tv_sec * (unsigned long)1000
			+ (_timeval.tv_usec / 1000)) % 1000000);
}

void	initialise_globals(t_globals *g_args)
{
	g_args->philo_amount = 4;
	g_args->time_to_die = 110;
	g_args->time_to_eat = 50;
	g_args->time_to_sleep = 50;
	g_args->simulate = false;
	g_args->ate_enough = false;
	g_args->times_philo_eat = 10;
}

void	end_cycle(t_globals *g_args)
{
	g_args->simulate = false;
	g_args->time_to_die = 0;
	g_args->time_to_eat = 0;
	g_args->time_to_sleep = 0;
}
