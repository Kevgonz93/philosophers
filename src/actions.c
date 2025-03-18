/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:37:29 by kegonza           #+#    #+#             */
/*   Updated: 2025/03/18 15:44:57 by kegonza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	has_died(t_philosopher *philosopher)
{
	t_program	*data_program;

	data_program = philosopher->program;
	pthread_mutex_lock(&philosopher->last_eat_mutex);
	if (get_time_ms() - philosopher->last_eat > data_program->time_to_die)
	{
		pthread_mutex_lock(&data_program->printer);
		printer(philosopher, "died");
		pthread_mutex_unlock(&data_program->printer);
		pthread_mutex_unlock(&philosopher->last_eat_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philosopher->last_eat_mutex);
	return (0);
}

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
	pthread_mutex_lock(&philosopher->last_eat_mutex);
	philosopher->last_eat = get_time_ms();
	pthread_mutex_unlock(&philosopher->last_eat_mutex);
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

// void	*routine(void *arg)
// {
// 	t_philosopher	*philosopher;
// 	t_program		*data_program;

// 	philosopher = (t_philosopher *)arg;
// 	data_program = philosopher->program;
// 	if (philosopher->id % 2 == 1)
// 	{
// 		to_eat(philosopher);
// 		pthread_mutex_lock(&data_program->printer);
// 		printer(philosopher, "has finished eating");
// 		pthread_mutex_unlock(&data_program->printer);
// 		to_sleep(philosopher);
// 	}
// 	else
// 		to_think(philosopher);
// 	while (1)
// 	{
// 		pthread_mutex_lock(&data_program->is_dead_mutex);
// 		if (data_program->is_dead)
// 		{
// 			pthread_mutex_unlock(&data_program->is_dead_mutex);
// 			break ;
// 		}
// 		pthread_mutex_unlock(&data_program->is_dead_mutex);
// 		to_think(philosopher);
// 		to_eat(philosopher);
// 		pthread_mutex_lock(&data_program->printer);
// 		printer(philosopher, "has finished eating");
// 		pthread_mutex_unlock(&data_program->printer);
// 		to_sleep(philosopher);
// 	}
// 	return (NULL);
// }


