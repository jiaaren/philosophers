/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 18:47:36 by jkhong            #+#    #+#             */
/*   Updated: 2021/08/20 19:40:34 by jkhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libphilo_bonus.h"

static t_globals		g_args;

int main(void)
{
	int	*child_pid;
	int num = 5;

	printf("\n");
	child_pid = initialise_process(num);
	if (child_pid == NULL)
		printf("I am a child!\n");
	else
	{
		for (int i = 0; i < num; i++)
			printf("%i\n", child_pid[i]);
		wait_children(num, child_pid);
		free(child_pid);
	}
	return (0);
}