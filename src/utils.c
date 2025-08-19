/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:37:41 by kegonza           #+#    #+#             */
/*   Updated: 2025/08/19 20:28:12 by kegonza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

long long	get_time_ms(void)
{
	struct timeval	time;
	long long		ms;

	gettimeofday(&time, NULL);
	ms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (ms);
}

void	printer(t_philosopher *philosopher, char *str)
{
	t_program	*data_program;

	data_program = philosopher->program;
	pthread_mutex_lock(&data_program->isover_mutex);
	if (data_program->is_over)
	{
		pthread_mutex_unlock(&data_program->isover_mutex);
		return ;
	}
	pthread_mutex_unlock(&data_program->isover_mutex);
	pthread_mutex_lock(&data_program->printer);
	printf("%lld Philo %d %s\n",
		get_time_ms() - data_program->start_time,
		philosopher->id, str);
	fflush(stdout);
	pthread_mutex_unlock(&data_program->printer);
}

long long	get_margin(t_program *data_program)
{
	long long	result;
	long long	tdie;
	long long	teat;
	long long	tsleep;

	tdie = data_program->time_to_die;
	teat = data_program->time_to_eat;
	tsleep = data_program->time_to_sleep;
	result = tdie - teat - tsleep;
	return (result);
}

int	print_usage(void)
{
	printf("-----------------------------------------------\n");
	printf("Usage: ./philosophers\n");
	printf("\tnumber_of_philosophers\n");
	printf("\ttime_to_die\n");
	printf("\ttime_to_eat\n");
	printf("\ttime_to_sleep\n");
	printf("\tnumber_of_times_each_philosopher_must_eat(optional)\n");
	printf("-----------------------------------------------\n");
	return (1);
}
