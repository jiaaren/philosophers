/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 14:40:46 by jkhong            #+#    #+#             */
/*   Updated: 2021/08/21 16:13:14 by jkhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libphilo_bonus.h"

int	main(int argc, char *argv[])
{
	t_globals	args;

	if (argc != 5)
	{
		printf("./philo [number_of_philosophers] [time_to_die] [time_to_eat] ");
		printf(" [time_to_sleep] \n");
		printf("Times are expressed in milliseconds (1 second = 1000 ms).\n");
		return (1);
	}
	if (initialise_globals(argc - 1, &(argv[1]), &args) == false)
	{
		printf("Please ensure all arguments are more than zero (> 0).\n");
		return (2);
	}
	philo_main(args);
	return (0);
}
