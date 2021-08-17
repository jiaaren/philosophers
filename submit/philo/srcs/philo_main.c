/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 17:46:14 by jkhong            #+#    #+#             */
/*   Updated: 2021/08/17 10:19:23 by jkhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libphilo.h"

static bool				g_simulate = false;
static pthread_mutex_t	*g_forks;
static t_globals		g_args;

__uint64_t givetime()
{
	struct timeval _timeval;

	gettimeofday(&_timeval, NULL);
	return(_timeval.tv_sec * (__uint64_t)1000 + (_timeval.tv_usec / 1000));
}

void	*test_thread(void *arg)
{
	int	i;

	i = 0;
	while (g_simulate)
	{
		if (i == 5)
			break ;
		printf("Starting thread %i\n", i++);
		sleep(1);
	}
	g_simulate = false;
}

/*
	Philo cycle
	- Think
	- Pick up forks (mutexes)
	- eat food (i.e. set time eaten)
		- how to have philosopher check time when holding fork??
	- sleep
*/

void	*test_thread2(void *arg)
{
	int		i;
	t_philo	*philo;

	philo = (t_philo *)(arg);
	while (!g_simulate)
		;
	philo->last_eat_time = givetime();
	i = 0;
	while (g_simulate)
	{
		if (i == 1)
			break ;
		printf("Philo num %i. Time: %lu\n", philo->philo_num, philo->last_eat_time);
		// printf("Phili num %i: has fork one as %i and for two as %i\n", philo->philo_num, philo->fork_one, philo->fork_two);
		i++;
		sleep(1);
	}
	g_simulate = false;
}



void	*initialise_philo(int p_num, t_philo **philo)
{
	t_philo	*tmp;
	int i;

	tmp = malloc(sizeof(t_philo) * p_num);
	i = 0;
	while (i < p_num)
	{
		tmp[i].philo_num = i + 1;
		tmp[i].times_eaten = 0;
		if (i != p_num - 1)
		{
			tmp[i].fork_one = i;
			tmp[i].fork_two = tmp[i].fork_one + 1;
		}
		else
		{
			tmp[i].fork_one = 0;
			tmp[i].fork_two = p_num - 1;
		}
		i++;
	}
	*philo = tmp;
}

void	initialise_globals(void)
{
	g_args.philo_amount = 0;
	g_args.time_to_die = 0;
	g_args.time_to_eat = 0;
	g_args.time_to_sleep = 0;
	g_args.times_philo_eat = 0;
}

/*
	Initialise forks(mutexes, and forks)
	- ordering seems important?
		1. initialise mutexes
		2. initialise pthread_create
		3. then only initialise pthread_join
*/
void	initialise_phil_forks(int p_num, pthread_t **thread, pthread_mutex_t **forks, t_philo *philo)
{
	int				i;
	pthread_t		*tmp_thread;
	pthread_mutex_t	*tmp_forks;

	i = 0;
	tmp_forks = malloc(sizeof(pthread_mutex_t) * p_num);
	while (i < p_num)
		pthread_mutex_init(&(tmp_forks[i++]), NULL);
	i = 0;
	tmp_thread = malloc(sizeof(pthread_t) * p_num);
	while (i < p_num)
		pthread_create(&(tmp_thread[i++]), NULL, test_thread2, (void *)&(philo[i]));
	g_simulate = true;
	i = 0;
	while (i < p_num)
		pthread_join(tmp_thread[i++], NULL);
	*thread = tmp_thread;
	*forks = tmp_forks;
}

void	free_threads(int p_num, pthread_t *thread, pthread_mutex_t *forks, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < p_num)
		pthread_mutex_destroy(&(forks[i++]));
	free(forks);
	free(thread);
	free(philo);
}

int	main(void)
{
	// constants to be replaced by argv
	int	num = 5;
	
	pthread_t	*thread;
	t_philo		*philo;

	initialise_philo(num, &philo);
	initialise_phil_forks(num, &thread, &g_forks, philo);
	while (g_simulate)
		;
	free_threads(num, thread, g_forks, philo);
	return (0);
}
