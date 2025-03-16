/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:37:34 by kegonza           #+#    #+#             */
/*   Updated: 2025/03/16 01:05:28 by kegonza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	forks_init(t_program *data_program)
{
	int	i;

	i = 0;
	data_program->forks = malloc(sizeof(pthread_mutex_t)
			* data_program->total_phil);
	if (!data_program->forks)
	{
		perror("Error: malloc");
		exit(1);
	}
	while (i < data_program->total_phil)
	{
		pthread_mutex_init(&data_program->forks[i], NULL);
		i++;
	}
}

void	init_mutex(t_program *data_program)
{
	pthread_mutex_init(&data_program->printer, NULL);
	pthread_mutex_init(&data_program->is_dead_mutex, NULL);
	forks_init(data_program);
}

void	destroy_mutex(t_program *data_program)
{
	int	i;

	i = 0;
	while (i < data_program->total_phil)
	{
		pthread_mutex_destroy(&data_program->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data_program->printer);
	pthread_mutex_destroy(&data_program->is_dead_mutex);
}
