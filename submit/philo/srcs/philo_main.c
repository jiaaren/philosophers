/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 17:46:14 by jkhong            #+#    #+#             */
/*   Updated: 2021/08/19 20:57:02 by jkhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libphilo.h"

static t_globals		g_args;
static pthread_mutex_t	*g_forks;

unsigned long	givetime(void)
{
	struct timeval	_timeval;

	gettimeofday(&_timeval, NULL);
	return ((_timeval.tv_sec * (unsigned long)1000
			+ (_timeval.tv_usec / 1000)) % 1000000);
}

void	takefork(t_philo *philo, int fork)
{
	pthread_mutex_lock(&(g_forks[fork]));
	if (g_args.simulate)
		printf("%lu %i has taken a fork\n", givetime(), philo->philo_num);
}

void	putfork(t_philo *philo)
{
	pthread_mutex_unlock(&(g_forks[philo->fork_one]));
	pthread_mutex_unlock(&(g_forks[philo->fork_two]));
}

void	end_cycle(void)
{
	g_args.simulate = false;
	g_args.time_to_die = 0;
	g_args.time_to_eat = 0;
	g_args.time_to_sleep = 0;
}

void	*death_th(void *arg)
{
	t_philo			*philo;
	unsigned long	wait_time;
	unsigned long	curr_time;

	philo = (t_philo *)(arg);
	wait_time = g_args.time_to_die;
	while (!(philo->last_eat_time))
		;
	while (g_args.simulate)
	{
		usleep(wait_time * 1000);
		curr_time = givetime();
		wait_time = (philo->last_eat_time + g_args.time_to_die) - curr_time;
		if (curr_time > (philo->last_eat_time + g_args.time_to_die)
			|| g_args.philo_amount == 1)
		{
			if (g_args.simulate)
				printf("%lu %i died\n", givetime(), philo->philo_num);
			end_cycle();
			putfork(philo);
			break ;
		}	
	}
}

void	eat(t_philo *philo)
{
	philo->last_eat_time = givetime();
	if (g_args.simulate)
		printf("%lu %i is eating\n", philo->last_eat_time, philo->philo_num);
	(philo->times_eaten)++;
	if (philo->times_eaten == g_args.times_philo_eat)
	{
		end_cycle();
		g_args.ate_enough = true;
		putfork(philo);
	}
	usleep(g_args.time_to_eat * 1000);
}

void	philo_sleep(t_philo *philo)
{
	if (g_args.simulate)
		printf("%lu %i is sleeping\n", givetime(), philo->philo_num);
	usleep(g_args.time_to_sleep * 1000);
}

void	think(t_philo *philo)
{
	if (g_args.simulate)
		printf("%lu %i is thinking\n", givetime(), philo->philo_num);
}

void	*philo_cycle(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)(arg);
	while (!g_args.simulate && !g_args.ate_enough)
		;
	philo->last_eat_time = givetime();
	while (g_args.simulate)
	{
		think(philo);
		takefork(philo, philo->fork_one);
		takefork(philo, philo->fork_two);
		eat(philo);
		putfork(philo);
		philo_sleep(philo);
	}
	return (NULL);
}

/*
	Initialise forks(mutexes, and forks)
	- ordering seems important?
		1. initialise mutexes
		2. initialise pthread_create
		3. then only initialise pthread_join
*/


void	initialise_globals(void)
{
	g_args.philo_amount = 4;
	g_args.time_to_die = 80;
	g_args.time_to_eat = 50;
	g_args.time_to_sleep = 50;
	g_args.simulate = false;
	g_args.ate_enough = false;
	g_args.times_philo_eat = __UINT32_MAX__;
}

int	main(void)
{
	pthread_t	*th_cycle;
	pthread_t	*th_death;
	t_philo		*philo;

	initialise_globals();
	initialise_philo(g_args.philo_amount, &philo);
	initialise_mutex(g_args.philo_amount, &g_forks);
	create_thread(g_args.philo_amount, &th_cycle, philo, philo_cycle);
	create_thread(g_args.philo_amount, &th_death, philo, death_th);
	g_args.simulate = true;
	join_and_free_th(g_args.philo_amount, th_cycle, th_death);
	free_mutex_fork_philo(g_args.philo_amount, g_forks, philo);
	return (0);
}
