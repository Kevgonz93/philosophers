/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:37:29 by kegonza           #+#    #+#             */
/*   Updated: 2025/03/23 21:12:15 by kegonza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	has_died(t_philosopher *philosopher)
{
	t_program	*data_program;

	data_program = philosopher->program;
	pthread_mutex_lock(&philosopher->last_eat_mutex);
	if ((get_time_ms() - philosopher->last_eat) > data_program->time_to_die)
	{
		printer(philosopher, "died");
		pthread_mutex_lock(&data_program->isover_mutex);
		data_program->is_over = 1;
		pthread_mutex_unlock(&data_program->isover_mutex);
		pthread_mutex_unlock(&philosopher->last_eat_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philosopher->last_eat_mutex);
	return (0);
}

void	*to_sleep(t_philosopher *philosopher)
{
	t_program	*data_program;

	data_program = philosopher->program;
	pthread_mutex_lock(&data_program->isover_mutex);
	if (data_program->is_over)
	{
		pthread_mutex_unlock(&data_program->isover_mutex);
		return (NULL);
	}
	pthread_mutex_unlock(&data_program->isover_mutex);
	printer(philosopher, "is sleeping");
	usleep(data_program->time_to_sleep * 1000);
	return (NULL);
}

void	*to_think(t_philosopher *philosopher)
{
	t_program	*data_program;

	data_program = philosopher->program;
	pthread_mutex_lock(&data_program->isover_mutex);
	if (data_program->is_over)
	{
		pthread_mutex_unlock(&data_program->isover_mutex);
		return (NULL);
	}
	pthread_mutex_unlock(&data_program->isover_mutex);
	printer(philosopher, "is thinking");
	usleep(data_program->time_to_eat / 2 * 1000);
	return (NULL);
}

void	*to_eat(t_philosopher *philosopher)
{
	t_program	*data_program;

	data_program = philosopher->program;
	if (philosopher->id % 2 != 0)
	{
		pthread_mutex_lock(&data_program->forks[philosopher->right_fork]);
		printer(philosopher, "has taken right fork");
		pthread_mutex_lock(&data_program->forks[philosopher->left_fork]);
		printer(philosopher, "has taken left fork");
	}
	else
	{
		pthread_mutex_lock(&data_program->forks[philosopher->left_fork]);
		printer(philosopher, "has taken left fork");
		pthread_mutex_lock(&data_program->forks[philosopher->right_fork]);
		printer(philosopher, "has taken right fork");
	}
	// pthread_mutex_lock(&data_program->isover_mutex);
	// if (data_program->is_over)
	// {
	// 	pthread_mutex_unlock(&data_program->isover_mutex);
	// 	pthread_mutex_unlock(&data_program->forks[philosopher->left_fork]);
	// 	pthread_mutex_unlock(&data_program->forks[philosopher->right_fork]);
	// 	return (NULL);
	// }
	// pthread_mutex_unlock(&data_program->isover_mutex);
	pthread_mutex_lock(&philosopher->last_eat_mutex);
	philosopher->last_eat = get_time_ms();
	pthread_mutex_unlock(&philosopher->last_eat_mutex);
	printer(philosopher, "is eating");
	usleep(data_program->time_to_eat * 1000);
	pthread_mutex_lock(&philosopher->eat_count_mutex);
	philosopher->eat_count++;
	pthread_mutex_unlock(&philosopher->eat_count_mutex);
	pthread_mutex_unlock(&data_program->forks[philosopher->left_fork]);
	pthread_mutex_unlock(&data_program->forks[philosopher->right_fork]);
	return (NULL);
}

void	*routine(void *arg)
{
	t_philosopher	*philosopher;
	t_program		*data_program;

	philosopher = (t_philosopher *)arg;
	data_program = philosopher->program;
	if (philosopher->id % 2 == 1)
		usleep(100);
	while (1)
	{
		pthread_mutex_lock(&data_program->isover_mutex);
		if (data_program->is_over)
		{
			pthread_mutex_unlock(&data_program->isover_mutex);
			break ;
		}
		pthread_mutex_unlock(&data_program->isover_mutex);
		to_eat(philosopher);
		printer(philosopher, "has finished eating");
		to_sleep(philosopher);
		to_think(philosopher);
	}
	return (NULL);
}


