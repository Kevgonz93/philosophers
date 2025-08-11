/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:37:29 by kegonza           #+#    #+#             */
/*   Updated: 2025/08/11 12:21:15 by kegonza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	lock_both_forks(t_philosopher *ph, int left, int right)
{
	int	first;
	int	second;

	second = right;
	first = left;

	if (first > second)
	{
		first = right;
		second = left;
	}
	pthread_mutex_lock(&ph->program->forks[first]);
	if (first == left)
		printer(ph, "has taken left fork");
	else
		printer(ph, "has taken right fork");
	pthread_mutex_lock(&ph->program->forks[second]);
	if (second == left)
		printer(ph, "has taken left fork");
	else
		printer(ph, "has taken right fork");
}

static void	unlock_both_forks(t_philosopher *ph, int left, int right)
{
	int	first;
	int	second;

	first = left;
	second = right;
	if (first > second)
	{
		first = right;
		second = left;
	}
	pthread_mutex_unlock(&ph->program->forks[second]);
	pthread_mutex_unlock(&ph->program->forks[first]);
}

void	*to_eat(t_philosopher *ph)
{
	int	left;
	int	right;

	left = ph->id - 1;
	right = (ph->id) % ph->program->total_phil;

	lock_both_forks(ph, left, right);

	printer(ph, "is eating");
	pthread_mutex_lock(&ph->last_eat_mutex);
	ph->last_eat = get_time_ms();
	pthread_mutex_unlock(&ph->last_eat_mutex);
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
	usleep((ph->program->time_to_eat / 2) * 1000);
	return (NULL);
}
