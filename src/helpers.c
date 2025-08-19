/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:50:44 by kegonza           #+#    #+#             */
/*   Updated: 2025/08/19 20:50:46 by kegonza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	reached_goal(t_philosopher *ph)
{
	int	target;
	int	count;
	int	done;

	target = ph->program->min_must_eat;
	pthread_mutex_lock(&ph->eat_count_mutex);
	count = ph->eat_count;
	pthread_mutex_unlock(&ph->eat_count_mutex);
	done = (target > 0 && count >= target);
	return (done);
}

static void	mark_last_eat(t_philosopher *ph)
{
	long long	now;

	pthread_mutex_lock(&ph->last_eat_mutex);
	now = get_time_ms();
	ph->last_eat = now;
	pthread_mutex_unlock(&ph->last_eat_mutex);
}

static void	inc_eat_capped(t_philosopher *ph)
{
	int	target;
	int	count;

	target = ph->program->min_must_eat;
	pthread_mutex_lock(&ph->eat_count_mutex);
	count = ph->eat_count;
	if (target <= 0 || count < target)
		ph->eat_count = count + 1;
	pthread_mutex_unlock(&ph->eat_count_mutex);
}

void	do_eat_phase(t_philosopher *ph, int left, int right)
{
	if (is_over(ph->program) || reached_goal(ph))
	{
		unlock_both_forks(ph, left, right);
		return ;
	}
	mark_last_eat(ph);
	printer(ph, "is eating");
	usleep(ph->program->time_to_eat * 1000);
	if (is_over(ph->program))
	{
		unlock_both_forks(ph, left, right);
		return ;
	}
	inc_eat_capped(ph);
	unlock_both_forks(ph, left, right);
}
