/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:37:34 by kegonza           #+#    #+#             */
/*   Updated: 2025/08/11 12:24:22 by kegonza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

// static void	forks_init(t_program *data_program)
// {
// 	int	i;
// 	int	ret;

// 	i = 0;
// 	data_program->forks = malloc(sizeof(pthread_mutex_t)
// 			* data_program->total_phil);
// 	if (!data_program->forks)
// 	{
// 		perror("Error: malloc");
// 		close_program(data_program, 1);
// 	}
// 	while (i < data_program->total_phil)
// 	{
// 		ret = pthread_mutex_init(&data_program->forks[i], NULL);
// 		if (ret != 0)
// 		{
// 			perror("Error: pthread_mutex_init");
// 			close_program(data_program, 1);
// 		}
// 		i++;
// 	}
// 	data_program->forks_init = 1;
// }

void	init_mutex(t_program *p)
{
	int i;

	pthread_mutex_init(&p->printer, NULL);
	p->printer_init = 1;
	pthread_mutex_init(&p->isover_mutex, NULL);
	p->isover_init = 1;

	p->forks = malloc(sizeof(*p->forks) * p->total_phil);
	i = 0;
	while (i < p->total_phil)
		pthread_mutex_init(&p->forks[i++], NULL);
	p->forks_init = 1;

	i = 0;
	while (i < p->total_phil)
	{
		pthread_mutex_init(&p->philosophers[i].last_eat_mutex, NULL);
		pthread_mutex_init(&p->philosophers[i].eat_count_mutex, NULL);
		i++;
	}
}

void	destroy_mutex(t_program *p)
{
	int	i;

	if (!p)
		return ;
	if (p->philosophers)
	{
		i = 0;
		while (i < p->total_phil)
		{
			pthread_mutex_destroy(&p->philosophers[i].last_eat_mutex);
			pthread_mutex_destroy(&p->philosophers[i].eat_count_mutex);
			i++;
		}
	}
	if (p->forks_init)
	{
		i = 0;
		while (i < p->total_phil)
			pthread_mutex_destroy(&p->forks[i++]);
	}
	if (p->isover_init)
		pthread_mutex_destroy(&p->isover_mutex);
	if (p->printer_init)
		pthread_mutex_destroy(&p->printer);
}
