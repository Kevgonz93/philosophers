/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:37:38 by kegonza           #+#    #+#             */
/*   Updated: 2025/08/11 12:25:09 by kegonza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	has_died(t_philosopher *ph)
{
	t_program	*p;
	int			died;

	p = ph->program;

	pthread_mutex_lock(&ph->last_eat_mutex);
	died = (get_time_ms() - ph->last_eat) > p->time_to_die;
	pthread_mutex_unlock(&ph->last_eat_mutex);

	if (died)
	{
		pthread_mutex_lock(&p->isover_mutex);
		if (!p->is_over)
		{
			pthread_mutex_unlock(&p->isover_mutex);
			pthread_mutex_lock(&p->printer);
			printf("%lld Philo %d died\n",
				get_time_ms() - p->start_time, ph->id);
			fflush(stdout);
			pthread_mutex_unlock(&p->printer);
			pthread_mutex_lock(&p->isover_mutex);
			p->is_over = 1;
		}
		pthread_mutex_unlock(&p->isover_mutex);
		return (1);
	}
	return (0);
}

static int	all_full(t_program *p)
{
	int	i;

	if (p->min_must_eat < 0)
		return (0);
	i = 0;
	while (i < p->total_phil)
	{
		pthread_mutex_lock(&p->philosophers[i].eat_count_mutex);
		if (p->philosophers[i].eat_count < p->min_must_eat)
		{
			pthread_mutex_unlock(&p->philosophers[i].eat_count_mutex);
			return (0);
		}
		pthread_mutex_unlock(&p->philosophers[i].eat_count_mutex);
		i++;
	}
	return (1);
}

void	*monitor(void *arg)
{
	t_program	*p;
	int			i;

	p = (t_program *)arg;
	i = 0;
	while (i < p->total_phil)
	{
		pthread_mutex_lock(&p->philosophers[i].last_eat_mutex);
		p->philosophers[i].last_eat = p->start_time;
		pthread_mutex_unlock(&p->philosophers[i].last_eat_mutex);
		i++;
	}
	while (1)
	{
		if (all_full(p))
			break ;
		i = 0;
		while (i < p->total_phil)
		{
			if (has_died(&p->philosophers[i]))
				return (NULL);
			i++;
		}
		usleep(1000);
	}
	pthread_mutex_lock(&p->isover_mutex);
	p->is_over = 1;
	pthread_mutex_unlock(&p->isover_mutex);
	return (NULL);
}

void	*routine(void *arg)
{
	t_philosopher	*ph;
	t_program		*p;

	ph = (t_philosopher *)arg;
	p = ph->program;

	if (ph->id % 2 == 0)
		usleep(500);

	while (1)
	{
		pthread_mutex_lock(&p->isover_mutex);
		if (p->is_over)
		{
			pthread_mutex_unlock(&p->isover_mutex);
			break ;
		}
		pthread_mutex_unlock(&p->isover_mutex);
		to_eat(ph);
		to_sleep(ph);
		to_think(ph);
	}
	return (NULL);
}

void	init_thread(t_philosopher *ph, t_program *p)
{
	int	i;

	pthread_create(&p->monitor, NULL, monitor, p);
	i = 0;
	while (i < p->total_phil)
	{
		pthread_create(&ph[i].thread, NULL, routine, &ph[i]);
		i++;
	}
}

void	finish_thread(t_program *p)
{
	int	i;

	pthread_join(p->monitor, NULL);
	i = 0;
	while (i < p->total_phil)
		pthread_join(p->philosophers[i++].thread, NULL);
}
