/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:37:41 by kegonza           #+#    #+#             */
/*   Updated: 2025/08/11 12:25:53 by kegonza          ###   ########.fr       */
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

// void	print_data(t_program *data_program)
// {
// 	int	i;

// 	i = 0;
// 	printf("-----------------------------------------------\n");
// 	printf("total_phil: %d\n", data_program->total_phil);
// 	printf("time_to_die: %lld\n", data_program->time_to_die);
// 	printf("time_to_eat: %lld\n", data_program->time_to_eat);
// 	printf("time_to_sleep: %lld\n", data_program->time_to_sleep);
// 	printf("min_must_eat: %d\n", data_program->min_must_eat);
// 	printf("start_time: %lld\n", data_program->start_time);
// 	printf("is_over: %d\n", data_program->is_over);
// 	printf("the philos are:\n");
// 	while (i < data_program->total_phil)
// 	{
// 		printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> PHILO %d\n", i + 1);
// 		printf("\tid: %d\n", data_program->philosophers[i].id);
// 		printf("\tleft_fork: %d\n", data_program->philosophers[i].left_fork);
// 		printf("\tright_fork: %d\n", data_program->philosophers[i].right_fork);
// 		printf("\ttimes_eaten: %d\n", data_program->philosophers[i].eat_count);
// 		printf("\tlast_meal: %lld\n", data_program->philosophers[i].last_eat);
// 		printf("\tis_dead: %d\n", data_program->is_over);
// 		i++;
// 	}
// 	printf("-----------------------------------------------\n");
// }

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
