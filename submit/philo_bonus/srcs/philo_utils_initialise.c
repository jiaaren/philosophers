/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_initialise.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 18:51:44 by jkhong            #+#    #+#             */
/*   Updated: 2021/08/27 00:37:13 by jkhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libphilo_bonus.h"

void wait_children(int p_num, int *child_pid)
{
    int i;

    i = 0;
    while (i < p_num)
        waitpid(child_pid[i++], NULL, 0);
}

void initialise_philo(t_philo *philo)
{
    philo->philo_num = 0;
    philo->last_eat_time = 0;
    philo->times_eaten = 0;
}

/*
	Handle freeing of malloc locally within function
	free when pid == 0, and return NULL
	if parent, return int array
*/
int *initialise_process(int p_num, t_philo *philo,
                        void *(death_cycle)(void *), void *(hear_one_death)(void *))
{
    int *child_pid;
    int pid;
    int i;

    child_pid = malloc(sizeof(int) * p_num);
    i = 0;
    while (i < p_num)
    {
        philo->philo_num = 1 + i;
        pid = fork();
        if (pid == 0)
            break;
        child_pid[i] = pid;
        i++;
    }
    if (pid != 0)
        return (child_pid);
    free(child_pid);
    pthread_create(&philo->th_death, NULL, death_cycle, (void *)0);
    pthread_create(&philo->th_hear_parent, NULL, hear_one_death, NULL);
    return (NULL);
}
