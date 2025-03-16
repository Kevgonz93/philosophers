/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:37:29 by kegonza           #+#    #+#             */
/*   Updated: 2025/03/16 01:07:05 by kegonza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*to_sleep(t_philosopher *philosopher)
{
	t_program	*data_program;
	long long	new_time;

	data_program = philosopher->program;
	pthread_mutex_lock(&data_program->printer);
	printer(philosopher, "is sleeping");
	pthread_mutex_unlock(&data_program->printer);
	new_time = get_time_ms();
	while (get_time_ms() - new_time < data_program->time_to_sleep)
		usleep(100);
	return (NULL);
}

void	*to_think(t_philosopher *philosopher)
{
	t_program	*data_program;

	data_program = philosopher->program;
	pthread_mutex_lock(&data_program->printer);
	printer(philosopher, "is thinking");
	pthread_mutex_unlock(&data_program->printer);
	return (NULL);
}

void	*to_eat(t_philosopher *philosopher)
{
	t_program	*data_program;
	long long	new_time;

	data_program = philosopher->program;
	pthread_mutex_lock(&data_program->forks[philosopher->left_fork]);
	pthread_mutex_lock(&data_program->forks[philosopher->right_fork]);
	pthread_mutex_lock(&data_program->printer);
	philosopher->last_eat = get_time_ms();
	printer(philosopher, "is eating");
	pthread_mutex_unlock(&data_program->printer);
	new_time = get_time_ms();
	while (get_time_ms() - new_time < data_program->time_to_eat)
		usleep(data_program->time_to_eat * 1000);
	pthread_mutex_unlock(&data_program->forks[philosopher->left_fork]);
	pthread_mutex_unlock(&data_program->forks[philosopher->right_fork]);
	philosopher->eat_count++;
	return (NULL);
}

void	*routine(void *arg)
{
	t_philosopher	*philosopher;
	t_program		*data_program;

	philosopher = (t_philosopher *)arg;
	data_program = philosopher->program;
	while (1)
	{
		to_think(philosopher);
		to_eat(philosopher);
		to_sleep(philosopher);
		pthread_mutex_lock(&data_program->printer);
		printer(philosopher, "has finished eating");
		pthread_mutex_unlock(&data_program->printer);
	}
	return (NULL);
}


