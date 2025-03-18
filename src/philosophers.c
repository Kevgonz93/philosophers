/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:37:38 by kegonza           #+#    #+#             */
/*   Updated: 2025/03/18 15:47:33 by kegonza          ###   ########.fr       */
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
				pthread_mutex_lock(&data_program->printer);
				printer(&data_program->philosophers[i], "died");
				pthread_mutex_unlock(&data_program->printer);
				close_program(data_program, 0);
			}
			i++;
		}
		usleep(1000);
	}
}

// void	init_thread(t_philosopher *philosophers, t_program *data_program)
// {
// 	int	i;
// 	int	ret;

// 	i = 0;
// 	while (i < data_program->total_phil)
// 	{
// 		ret = pthread_create(&philosophers[i].thread, NULL,
// 				&routine, &philosophers[i]);
// 		if (ret != 0)
// 		{
// 			perror("Error: pthread_create");
// 			close_program(data_program, 1);
// 		}
// 		i++;
// 	}
// 	ret = pthread_create(&data_program->monitor, NULL, &monitor, data_program);
// 	if (ret != 0)
// 	{
// 		perror("Error: pthread_create");
// 		close_program(data_program, 1);
// 	}
// 	i = 0;
// 	while (i < data_program->total_phil)
// 	{
// 		pthread_join(philosophers[i].thread, NULL);
// 		i++;
// 	}
// 	pthread_join(&data_program->monitor, NULL);
// }

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
		philosopher[i].eat_count = 0;
		philosopher[i].last_eat = get_time_ms();
		philosopher[i].program = data_program;
		if (i % 2 == 0)
		{
			philosopher[i].left_fork = i;
			philosopher[i].right_fork = (i + 1) % data_program->total_phil;
		}
		else
		{
			philosopher[i].left_fork = (i + 1) % data_program->total_phil;
			philosopher[i].right_fork = i;
		}
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
