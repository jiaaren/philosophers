/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 19:57:57 by jkhong            #+#    #+#             */
/*   Updated: 2021/08/19 20:28:48 by jkhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libphilo.h"

void	initialise_philo(int p_num, t_philo **philo)
{
	t_philo	*tmp;
	int		i;

	tmp = malloc(sizeof(t_philo) * p_num);
	i = 0;
	while (i < p_num)
	{
		tmp[i].philo_num = i + 1;
		tmp[i].times_eaten = 0;
		tmp[i].last_eat_time = 0;
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

void	initialise_mutex(int p_num, pthread_mutex_t **forks)
{
	pthread_mutex_t	*tmp_forks;
	int				i;

	i = 0;
	tmp_forks = malloc(sizeof(pthread_mutex_t) * p_num);
	while (i < p_num)
		pthread_mutex_init(&(tmp_forks[i++]), NULL);
	*forks = tmp_forks;
}

void	free_threads(int p_num, pthread_t *thread,
		pthread_mutex_t *forks, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < p_num)
		pthread_mutex_destroy(&(forks[i++]));
	free(forks);
	free(thread);
	free(philo);
}