/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 18:47:36 by jkhong            #+#    #+#             */
/*   Updated: 2021/08/21 14:59:07 by jkhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libphilo_bonus.h"

static t_globals	g_args;
static t_philo		g_philo;
static t_sems		g_sems;

void	*hear_one_death(void *arg)
{
	sem_wait(g_sems.end);
	end_cycle(&g_args);
	sem_post(g_sems.end);
	g_args.threads_ended++;
	return (NULL);
}

void	*death_cycle(void *arg)
{
	unsigned long	wait_time;
	unsigned long	curr_time;

	wait_time = g_args.time_to_die;
	while (!(g_philo.last_eat_time))
		;
	while (g_args.simulate)
	{
		usleep(wait_time * 1000);
		curr_time = givetime();
		wait_time = (g_philo.last_eat_time + g_args.time_to_die) - curr_time;
		if (curr_time >= (g_philo.last_eat_time + g_args.time_to_die)
			|| g_args.philo_amount == 1)
		{
			if (g_args.simulate)
				printf("%lu %i died\n", givetime(), g_philo.philo_num);
			sem_post(g_sems.end);
			end_cycle(&g_args);
			sem_post(g_sems.forks);
			sem_post(g_sems.forks);
			break ;
		}	
	}
	g_args.threads_ended++;
	return (NULL);
}

void	eat(void)
{
	g_philo.last_eat_time = givetime();
	if (g_args.simulate)
		printf("%lu %i is eating\n", g_philo.last_eat_time, g_philo.philo_num);
	// (g_philo.times_eaten)++;
	// if (g_philo.times_eaten >= g_args.times_philo_eat)
	// 	g_args.tummies_filled++;
	// if (g_args.tummies_filled >= g_args.philo_amount)
	// {
	// 	end_cycle(&g_args);
	// 	g_args.ate_enough = true;
	// 	putforks(philo);
	// }
	usleep(g_args.time_to_eat * 1000);
}

void	philo_cycle(void)
{
	g_args.simulate = true;
	g_philo.last_eat_time = givetime();
	while (g_args.simulate)
	{
		if (g_args.simulate)
			printf("%lu %i is thinking\n", givetime(), g_philo.philo_num);
		sem_wait(g_sems.forks);
		if (g_args.simulate)
			printf("%lu %i has taken a fork\n", givetime(), g_philo.philo_num);
		sem_wait(g_sems.forks);
		if (g_args.simulate)
			printf("%lu %i has taken a fork\n", givetime(), g_philo.philo_num);
		eat();
		sem_post(g_sems.forks);
		sem_post(g_sems.forks);
		if (g_args.simulate)
			printf("%lu %i is sleeping\n", givetime(), g_philo.philo_num);
		usleep(g_args.time_to_sleep * 1000);
	}
}

void	philo_main(t_globals args)
{
	int		*child_pid;

	g_args = args;
	initialise_philo(&g_philo);
	initialise_all_sems(g_args.philo_amount, &g_sems);
	child_pid = initialise_process(g_args.philo_amount,
			&g_philo, death_cycle, hear_one_death);
	if (child_pid == NULL)
	{
		sem_wait(g_sems.start);
		philo_cycle();
		while (g_args.threads_ended != 2)
			;
		usleep(100000);
		close_all_sems(&g_sems);
	}
	else
	{
		commence_cycle(g_sems.start, g_args.philo_amount);
		wait_children(g_args.philo_amount, child_pid);
		free(child_pid);
		// run parent process
		close_all_sems(&g_sems);
	}
}
