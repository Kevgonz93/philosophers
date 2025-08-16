/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:37:29 by kegonza           #+#    #+#             */
/*   Updated: 2025/08/17 00:57:45 by kegonza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

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

void	*to_eat(t_philosopher *ph)
{
	int	left;
	int	right;

	if (ph->program->total_phil == 1)
	{
		printer(ph, "has taken a fork");
		usleep(ph->program->time_to_die * 1000);
		return (NULL);
}
	left = ph->id - 1;
	right = (ph->id) % ph->program->total_phil;
	lock_both_forks(ph, left, right);
	pthread_mutex_lock(&ph->last_eat_mutex);
	ph->last_eat = get_time_ms();
	pthread_mutex_unlock(&ph->last_eat_mutex);
	printer(ph, "is eating");
	usleep(ph->program->time_to_eat * 1000);
	pthread_mutex_lock(&ph->eat_count_mutex);
	ph->eat_count++;
	pthread_mutex_unlock(&ph->eat_count_mutex);
	unlock_both_forks(ph, left, right);
	return (NULL);
}

void	*to_sleep(t_philosopher *ph)
{
	printer(ph, "is sleeping");
	usleep(ph->program->time_to_sleep * 1000);
	return (NULL);
}

void	*to_think(t_philosopher *ph)
{

	printer(ph, "is thinking");
	if (ph->program->margin / 2 <= 5)
		return (NULL);
	else
		usleep((ph->program->time_to_eat / 2) * 1000);
	return (NULL);
}
