/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:37:29 by kegonza           #+#    #+#             */
/*   Updated: 2025/08/19 20:53:01 by kegonza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	do_cycle(t_philosopher *ph)
{
	to_eat(ph);
	if (is_over(ph->program))
		return ;
	to_sleep(ph);
	if (is_over(ph->program))
		return ;
	to_think(ph);
}

void	*routine(void *arg)
{
	t_philosopher	*ph;
	t_program		*p;

	ph = (t_philosopher *)arg;
	p = ph->program;
	if (ph->id % 2 == 0)
		usleep(500);
	while (!is_over(p))
		do_cycle(ph);
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
	if (is_over(ph->program) || reached_goal(ph))
		return (NULL);
	left = ph->id - 1;
	right = ph->id % ph->program->total_phil;
	lock_both_forks(ph, left, right);
	do_eat_phase(ph, left, right);
	return (NULL);
}

// void	*to_eat(t_philosopher *ph)
// {
// 	int	left;
// 	int	right;

// 	if (ph->program->total_phil == 1)
// 	{
// 		printer(ph, "has taken a fork");
// 		usleep(ph->program->time_to_die * 1000);
// 		return (NULL);
// 	}
// 	pthread_mutex_lock(&ph->program->isover_mutex);
// 	if (ph->program->is_over)
// 	{
// 		pthread_mutex_unlock(&ph->program->isover_mutex);
// 		return (NULL);
// 	}
// 	pthread_mutex_unlock(&ph->program->isover_mutex);
// 	left = ph->id - 1;
// 	right = (ph->id) % ph->program->total_phil;
// 	lock_both_forks(ph, left, right);
// 	pthread_mutex_lock(&ph->program->isover_mutex);
// 	if (ph->program->is_over)
// 	{
// 		unlock_both_forks(ph, left, right);
// 		pthread_mutex_unlock(&ph->program->isover_mutex);
// 		return (NULL);
// 	}
// 	pthread_mutex_unlock(&ph->program->isover_mutex);
// 	pthread_mutex_lock(&ph->last_eat_mutex);
// 	ph->last_eat = get_time_ms();
// 	pthread_mutex_unlock(&ph->last_eat_mutex);
// 	printer(ph, "is eating");
// 	usleep(ph->program->time_to_eat * 1000);
// 	pthread_mutex_lock(&ph->program->isover_mutex);
// 	if (ph->program->is_over)
// 	{
// 		unlock_both_forks(ph, left, right);
// 		pthread_mutex_unlock(&ph->program->isover_mutex);
// 		return (NULL);
// 	}
// 	pthread_mutex_unlock(&ph->program->isover_mutex);
// 	pthread_mutex_lock(&ph->eat_count_mutex);
// 	ph->eat_count++;
// 	pthread_mutex_unlock(&ph->eat_count_mutex);
// 	unlock_both_forks(ph, left, right);
// 	return (NULL);
// }

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
