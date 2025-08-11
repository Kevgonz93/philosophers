/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonzal <kegonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 13:42:53 by kegonzal          #+#    #+#             */
/*   Updated: 2025/08/11 14:35:51 by kegonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	lock_both_forks(t_philosopher *ph, int left, int right)
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

void	unlock_both_forks(t_philosopher *ph, int left, int right)
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
