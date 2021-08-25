/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 17:46:14 by jkhong            #+#    #+#             */
/*   Updated: 2021/08/25 17:54:12 by jkhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libphilo.h"

static t_globals		g_args;
static pthread_mutex_t	*g_forks;
static pthread_mutex_t	*g_seq;

void	print_status(char *str, int p_num)
{
	pthread_mutex_lock(&(g_seq[p_num - 1]));
	if (g_args.simulate)
		printf(str, givetime(), p_num);
	pthread_mutex_unlock(&(g_seq[p_num - 1]));
}

void	putforks(t_philo *philo)
{
	pthread_mutex_unlock(&(g_forks[philo->fork_one]));
	pthread_mutex_unlock(&(g_forks[philo->fork_two]));
}

void	*death_cycle(void *arg)
{
	t_philo	*philo;
	size_t	wait_time;
	size_t	curr_time;

	philo = (t_philo *)(arg);
	wait_time = g_args.time_to_die;
	while (!(philo->last_eat_time))
		;
	while (g_args.simulate)
	{
		ft_usleep(wait_time * 1000);
		curr_time = givetime();
		wait_time = (philo->last_eat_time + g_args.time_to_die) - curr_time;
		if (curr_time > (philo->last_eat_time + g_args.time_to_die)
			|| g_args.philo_amount == 1)
		{
			pthread_mutex_lock(&(g_seq[philo->philo_num - 1]));
			if (g_args.simulate)
				printf("%lu %i died\n", givetime(), philo->philo_num);
			end_cycle(&g_args);
			pthread_mutex_unlock(&(g_seq[philo->philo_num - 1]));
			putforks(philo);
			break ;
		}
	}
	return (NULL);
}

void	eat(t_philo *philo)
{
	philo->last_eat_time = givetime();
	print_status("%lu %i is eating\n", philo->philo_num);
	(philo->times_eaten)++;
	if (philo->times_eaten >= g_args.times_philo_eat)
		g_args.tummies_filled++;
	if (g_args.tummies_filled >= g_args.philo_amount)
	{
		end_cycle(&g_args);
		g_args.ate_enough = true;
		putforks(philo);
	}
	ft_usleep(g_args.time_to_eat * 1000);
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
		print_status("%lu %i is thinking\n", philo->philo_num);
		pthread_mutex_lock(&(g_forks[philo->fork_one]));
		print_status("%lu %i has taken a fork\n", philo->philo_num);
		pthread_mutex_lock(&(g_forks[philo->fork_two]));
		print_status("%lu %i has taken a fork\n", philo->philo_num);
		eat(philo);
		putforks(philo);
		print_status("%lu %i is sleeping\n", philo->philo_num);
		ft_usleep(g_args.time_to_sleep * 1000);
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
int	main(int argc, char *argv[])
{
	pthread_t	*th_cycle;
	pthread_t	*th_death;
	t_philo		*philo;

	if (argc != 5 && argc != 6)
	{
		printf("./philo [number_of_philosophers] [time_to_die] [time_to_eat] ");
		printf(" [time_to_sleep] ");
		printf(" [OPTIONAL: number_of_times_each_philosopher_must_eat]\n");
		printf("Times are expressed in milliseconds (1 second = 1000 ms).\n");
		return (1);
	}
	if (initialise_globals(argc - 1, &(argv[1]), &g_args) == false)
	{
		printf("Please ensure all arguments are more than zero (> 0).\n");
		return (2);
	}
	initialise_philo(g_args.philo_amount, &philo);
	initialise_mutex(g_args.philo_amount, &g_forks, &g_seq);
	create_thread(g_args.philo_amount, &th_cycle, philo, philo_cycle);
	create_thread(g_args.philo_amount, &th_death, philo, death_cycle);
	g_args.simulate = true;
	join_and_free_th(g_args.philo_amount, th_cycle, th_death);
	free_mutex_fork_philo(g_args.philo_amount, g_forks, g_seq, philo);
	return (0);
}
