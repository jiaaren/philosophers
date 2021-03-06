/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_others.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 19:52:55 by jkhong            #+#    #+#             */
/*   Updated: 2021/08/22 11:45:49 by jkhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libphilo_bonus.h"

size_t	givetime(void)
{
	struct timeval	_timeval;

	gettimeofday(&_timeval, NULL);
	return ((_timeval.tv_sec * (size_t)1000
			+ (_timeval.tv_usec / 1000)) % 1000000);
}

void	ft_usleep(unsigned int n)
{
	struct timeval	start;
	struct timeval	step;

	gettimeofday(&start, NULL);
	while (true)
	{
		usleep(50);
		gettimeofday(&step, NULL);
		if ((size_t)(((size_t)(step.tv_sec - start.tv_sec)) * 1000000 +
				((size_t)(step.tv_usec - start.tv_usec))) > n)
			break ;
	}
}

int	ft_atoi(const char *str)
{
	long	num;
	long	neg;

	num = 0;
	neg = 1;
	while (*str == ' ' || *str == '\f' || *str == '\n'
		|| *str == '\r' || *str == '\t' || *str == '\v')
		str++;
	if (*str == '-')
		neg *= -1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		num = (num * 10) + (*str - '0');
		str++;
	}
	num = num * neg;
	if (num < -2147483648 || num > 2147483647)
	{
		if (neg == 1)
			return (-1);
		return (0);
	}
	return ((int)num);
}

// pass in argc - 1 for params
// pass in &(argv[1]) for args
bool	initialise_globals(int params, char *args[], t_globals	*g_args)
{
	static int	i = -1;
	int			num;

	while (++i < params)
	{
		num = ft_atoi(args[i]);
		if (num <= 0)
			return (false);
		else if (i == 0)
			g_args->philo_amount = num;
		else if (i == 1)
			g_args->time_to_die = num;
		else if (i == 2)
			g_args->time_to_eat = num;
		else if (i == 3)
			g_args->time_to_sleep = num;
		else
			g_args->times_philo_eat = num;
	}
	if (params == 4)
		g_args->times_philo_eat = INT_MAX;
	g_args->simulate = false;
	return (true);
}

void	end_cycle(t_globals *g_args)
{
	g_args->simulate = false;
	g_args->time_to_die = 0;
	g_args->time_to_eat = 0;
	g_args->time_to_sleep = 0;
}
