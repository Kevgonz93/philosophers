/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closep.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 00:44:56 by kegonza           #+#    #+#             */
/*   Updated: 2025/03/20 01:34:49 by kegonza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/philosophers.h"

void	close_program(t_program *data_program, int fail)
{
	if (data_program)
	{
		destroy_mutex(data_program);
		if (data_program->forks)
			free(data_program->forks);
		if (data_program->philosophers)
			free(data_program->philosophers);
		free(data_program);
	}
	printf("closing program\n");
	if (fail == 1)
		exit(1);
	exit(0);
}
