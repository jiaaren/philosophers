/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 17:46:14 by jkhong            #+#    #+#             */
/*   Updated: 2021/08/17 13:54:22 by jkhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libphilo.h"

static bool				g_simulate = false;
static pthread_mutex_t	*g_forks;
static t_globals		g_args;

unsigned long givetime()
{
	struct timeval _timeval;

	gettimeofday(&_timeval, NULL);
	return((_timeval.tv_sec * (unsigned long)1000 + (_timeval.tv_usec / 1000)) % 1000000);
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
	return (NULL);
}

/*
	Philo cycle
	- Think
	- Pick up forks (mutexes)
	- eat food (i.e. set time eaten)
		- how to have philosopher check time when holding fork??
	- sleep
*/

void	takefork(t_philo *philo, int fork)
{
	pthread_mutex_lock(&(g_forks[fork]));
	printf("%lu %i has taken a fork\n", givetime(), philo->philo_num);	
}

void	putfork(t_philo *philo)
{
	pthread_mutex_unlock(&(g_forks[philo->fork_one]));
	pthread_mutex_unlock(&(g_forks[philo->fork_two]));	
}

void	*death_thread(void *arg)
{
	const t_philo *philo = (t_philo *)(arg);

	while (givetime() <= (philo->last_eat_time + g_args.time_to_die))
		;
	printf("%lu %i died\n", givetime(), philo->philo_num);
	putfork((t_philo *)philo);
	g_simulate = false;
}

void	eat(t_philo *philo)
{
	printf("%lu %i is eating\n", givetime(), philo->philo_num);	
	philo->last_eat_time = givetime();
	pthread_create(&philo->check_death, NULL, death_thread, (void *)philo);
	usleep(g_args.time_to_eat * 1000);
	putfork(philo);
	pthread_detach(philo->check_death);
}

void	philo_sleep(t_philo *philo)
{
	printf("%lu %i is sleeping\n", givetime(), philo->philo_num);
	usleep(g_args.time_to_sleep * 1000);
}

void	think(t_philo *philo)
{
	printf("%lu %i is thinking\n", givetime(), philo->philo_num);
}

void	*test_thread2(void *arg)
{
	int			i;
	t_philo		*philo;

	philo = (t_philo *)(arg);
	while (!g_simulate)
		;
	philo->last_eat_time = givetime();
	i = 0;
	pthread_create(&philo->check_death, NULL, death_thread, (void *)philo);
	while (g_simulate)
	{
		think(philo);
		takefork(philo, philo->fork_one);
		takefork(philo, philo->fork_two);
		eat(philo);
		philo_sleep(philo);
	}
	return (NULL);
}

void	initialise_philo(int p_num, t_philo **philo)
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
	g_args.philo_amount = 5;
	g_args.time_to_die = 200;
	g_args.time_to_eat = 100;
	g_args.time_to_sleep = 50;
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
	*forks = tmp_forks;
	i = 0;
	tmp_thread = malloc(sizeof(pthread_t) * p_num);
	while (i < p_num)
		pthread_create(&(tmp_thread[i++]), NULL, test_thread2, (void *)&(philo[i]));
	g_simulate = true;
	// i = 0;
	// while (i < p_num)
	// 	pthread_join(tmp_thread[i++], NULL);
	*thread = tmp_thread;
}

void	free_threads(int p_num, pthread_t *thread, pthread_mutex_t *forks, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < p_num)
		pthread_detach(thread[i++]);
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
	pthread_t	*thread;
	t_philo		*philo;

	initialise_globals();
	initialise_philo(5, &philo);
	initialise_phil_forks(5, &thread, &g_forks, philo);
	while (g_simulate)
		;
	free_threads(5, thread, g_forks, philo);
	return (0);
}
