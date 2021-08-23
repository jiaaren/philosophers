/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_initialise.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 19:57:57 by jkhong            #+#    #+#             */
/*   Updated: 2021/08/23 12:30:50 by jkhong           ###   ########.fr       */
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
		if (i % 2 == 0)
		{
			tmp[i].fork_one = i;
			tmp[i].fork_two = (i + 1) % p_num;
		}
		else
		{
			tmp[i].fork_two = i;
			tmp[i].fork_one = (i + 1) % p_num;
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

void	create_thread(int p_num, pthread_t **thread,
			t_philo *philo, void *(f)(void *))
{
	int				i;
	pthread_t		*th;

	th = malloc(sizeof(pthread_t) * p_num);
	i = 0;
	while (i < p_num)
	{
		pthread_create(&(th[i]), NULL, f, (void *)(&(philo[i])));
		i++;
	}
	*thread = th;
}

void	join_and_free_th(int p_num, pthread_t *th_cycle, pthread_t *th_death)
{
	int	i;

	i = 0;
	while (i < p_num)
	{
		pthread_join(th_cycle[i], NULL);
		pthread_join(th_death[i], NULL);
		i++;
	}
	free(th_cycle);
	free(th_death);
}

void	free_mutex_fork_philo(int p_num, pthread_mutex_t *forks, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < p_num)
		pthread_mutex_destroy(&(forks[i++]));
	free(forks);
	free(philo);
}
