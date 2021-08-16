/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 17:46:14 by jkhong            #+#    #+#             */
/*   Updated: 2021/08/16 18:30:30 by jkhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libphilo.h"

bool	g_simulate = true;

void	*test_thread (void *arg)
{
	while (g_simulate)
	{
		sleep(1);
		printf("Starting thread\n");
	}
}

void	*end_thread (void *arg)
{
	sleep(5);
	g_simulate = false;
}

void	initialise_phil_forks(int p_num, pthread_t **philo)
{
	int			i;
	pthread_t	*tmp;

	i = 0;
	tmp = malloc(sizeof(pthread_t) * p_num);
	while (i < p_num - 1)
		pthread_create(&(tmp[i++]), NULL, test_thread, NULL);
	pthread_create(&(tmp[4]), NULL, end_thread, NULL);
	i = 0;
	while (i < p_num - 1)
		pthread_join(tmp[i++], NULL);
	pthread_join(tmp[4], NULL);
	*philo = tmp;
}

void	free_threads(pthread_t *philo)
{
	free(philo);
}

int main(void)
{
	// constants to be replaced by argv
	int	num = 5;

	pthread_t *philo;
	initialise_phil_forks(num, &philo);

	free_threads(philo);
	return (0);
}