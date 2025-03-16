/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:37:38 by kegonza           #+#    #+#             */
/*   Updated: 2025/03/16 00:46:39 by kegonza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	init_thread(t_philosopher *philosophers, t_program *data_program)
{
	int	i;
	int ret;

	i = 0;
	while (i < data_program->total_phil)
	{
		ret = pthread_create(&philosophers[i].thread, NULL,
				&routine, &philosophers[i]);
		if (!ret)
		{
			perror("Error: pthread_create");
			exit(1);
		}
		i++;
	}
	i = 0;
	while (i < data_program->total_phil)
	{
		pthread_join(philosophers[i].thread, NULL);
		i++;
	}
}

t_philosopher	*create_philosophers(t_program *data_program)
{
	t_philosopher *philosopher;
	int i;

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
		philosopher[i].left_fork = i;
		philosopher[i].right_fork = (i + 1) % data_program->total_phil;
		i++;
	}
	return (philosopher);
}
