/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 17:46:14 by jkhong            #+#    #+#             */
/*   Updated: 2021/08/16 19:05:39 by jkhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libphilo.h"

static bool			g_simulate = true;
pthread_mutex_t		*g_forks;

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


/*
	Initialise forks(mutexes, and forks)
	- ordering seems important?
		1. initialise mutexes
		2. initialise pthread_create
		3. then only initialise pthread_join
*/
void	initialise_phil_forks(int p_num, pthread_t **philo, pthread_mutex_t **forks)
{
	int				i;
	pthread_t		*tmp_philo;
	pthread_mutex_t	*tmp_forks;

	i = 0;
	tmp_forks = malloc(sizeof(pthread_mutex_t) * p_num);
	while (i < p_num)
		pthread_mutex_init(&(tmp_forks[i++]), NULL);
	i = 0;
	tmp_philo = malloc(sizeof(pthread_t) * p_num);
	while (i < p_num)
		pthread_create(&(tmp_philo[i++]), NULL, test_thread, NULL);
	i = 0;
	while (i < p_num)
		pthread_join(tmp_philo[i++], NULL);
	*philo = tmp_philo;
	*forks = tmp_forks;
}

void	free_threads(int p_num, pthread_t *philo, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < p_num)
		pthread_mutex_destroy(&(forks[i++]));
	free(forks);
	free(philo);
}

int	main(void)
{
	// constants to be replaced by argv
	int	num = 5;
	
	pthread_t	*philo;

	initialise_phil_forks(num, &philo, &g_forks);
	while (g_simulate)
		;
	free_threads(num, philo, g_forks);
	return (0);
}
