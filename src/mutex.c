/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonzal <kegonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:37:34 by kegonza           #+#    #+#             */
/*   Updated: 2025/08/11 14:03:00 by kegonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	init_mutex(t_program *p)
{
	int	i;

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
