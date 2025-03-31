/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:37:38 by kegonza           #+#    #+#             */
/*   Updated: 2025/03/21 19:56:10 by kegonza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*monitor(void *arg)
{
	t_program		*data_program;
	int				i;

	data_program = (t_program *)arg;
	while (1)
	{
		i = 0;
		while (i < data_program->total_phil)
		{
			if (has_died(&data_program->philosophers[i]))
			{
				pthread_mutex_lock(&data_program->isover_mutex);
				data_program->is_over = 1;
				pthread_mutex_unlock(&data_program->isover_mutex);
				close_program(data_program, 0);
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

void	finish_thread(t_program *data_program)
{
	int	i;
	int	ret;

	data_program->is_over = 1;
	i = 0;
	while (i < data_program->total_phil)
	{
		ret = pthread_join(data_program->philosophers[i].thread, NULL);
		if (ret != 0)
		{
			perror("Error: pthread_join philo");
			close_program(data_program, 1);
		}
		i++;
	}
	ret = pthread_join(data_program->monitor, NULL);
	if (ret != 0)
	{
		perror("Error: pthread_join monitor");
		close_program(data_program, 1);
	}
}

void	init_thread(t_philosopher *philosophers, t_program *data_program)
{
	int	i;
	int	ret;

	ret = pthread_create(&data_program->monitor, NULL, monitor, data_program);
	if (ret != 0)
	{
		perror("Error: pthread_create");
		close_program(data_program, 1);
	}
	i = 0;
	while (i < data_program->total_phil)
	{
		ret = pthread_create(&philosophers[i].thread, NULL,
				routine, &philosophers[i]);
		if (ret != 0)
		{
			perror("Error: pthread_create");
			close_program(data_program, 1);
		}
		i++;
	}
}

t_philosopher	*create_philosophers(t_program *data_program)
{
	t_philosopher	*philosopher;
	int				i;
	int				ret;

	i = 0;
	philosopher = malloc(sizeof(t_philosopher) * data_program->total_phil);
	if (!philosopher)
	{
		perror("Error: philo malloc");
		exit(1);
	}
	while (i < data_program->total_phil)
	{
		philosopher[i].id = i + 1;
		philosopher[i].left_fork = i;
		philosopher[i].right_fork = (i + 1) % data_program->total_phil;
		philosopher[i].eat_count = 0;
		philosopher[i].last_eat = get_time_ms();
		philosopher[i].program = data_program;
		ret = pthread_mutex_init(&philosopher[i].last_eat_mutex, NULL);
		if (ret != 0)
		{
			perror("Error: pthread_mutex_init");
			close_program(data_program, 1);
		}
		i++;
	}
	return (philosopher);
}
