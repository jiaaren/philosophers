/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libphilo.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 17:51:50 by jkhong            #+#    #+#             */
/*   Updated: 2021/08/17 10:12:07 by jkhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef LIBPHILO_H
# define LIBPHILO_H

#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/time.h>

typedef struct  s_globals {
    int philo_amount;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int times_philo_eat;
}               t_globals;

typedef struct  s_philo {
    int philo_num;
    __uint64_t last_eat_time;
    int times_eaten;
    int fork_one;
    int fork_two;
}               t_philo;

# endif
