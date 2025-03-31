/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:37:34 by kegonza           #+#    #+#             */
/*   Updated: 2025/03/21 19:25:35 by kegonza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	forks_init(t_program *data_program)
{
	int	i;
	int	ret;

	i = 0;
	data_program->forks = malloc(sizeof(pthread_mutex_t)
			* data_program->total_phil);
	if (!data_program->forks)
	{
		perror("Error: malloc");
		close_program(data_program, 1);
	}
	while (i < data_program->total_phil)
	{
		ret = pthread_mutex_init(&data_program->forks[i], NULL);
		if (ret != 0)
		{
			perror("Error: pthread_mutex_init");
			close_program(data_program, 1);
		}
		data_program->forks_init = 1;
		i++;
	}
}

void	init_mutex(t_program *data_program)
{
	int	i;

	i = 0;
	printf("intiating mutexs\n");
	pthread_mutex_init(&data_program->isover_mutex, NULL);
	data_program->monitor_init = 1;
	pthread_mutex_init(&data_program->printer, NULL);
	data_program->printer_init = 1;
	while (i < data_program->total_phil)
	{
		pthread_mutex_init(
			&data_program->philosophers[i].eat_count_mutex, NULL);
		data_program->philosophers[i].eat_count_init = 1;
		pthread_mutex_init(&data_program->philosophers[i].last_eat_mutex, NULL);
		data_program->philosophers[i].last_eat_init = 1;
		i++;
	}
	forks_init(data_program);
}

void	destroy_mutex(t_program *data_program)
{
	int	i;

	i = 0;
	if (data_program->forks_init)
	{
		while (i < data_program->total_phil)
			pthread_mutex_destroy(&data_program->forks[i++]);
	}
	else if (data_program->monitor_init)
		pthread_mutex_destroy(&data_program->isover_mutex);
	else if (data_program->printer_init)
		pthread_mutex_destroy(&data_program->printer);
	else if (data_program->philosophers)
	{
		while (i < data_program->total_phil)
		{
			if (data_program->philosophers[i].eat_count_init)
				pthread_mutex_destroy(
					&data_program->philosophers[i].eat_count_mutex);
			if (data_program->philosophers[i].last_eat_init)
				pthread_mutex_destroy(
					&data_program->philosophers[i].last_eat_mutex);
			i--;
		}
	}
}
