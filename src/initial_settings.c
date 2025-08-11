/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial_settings.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:57:04 by kegonza           #+#    #+#             */
/*   Updated: 2025/08/11 12:27:47 by kegonza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	check_params(t_program *data_program)
{
	int	count;

	count = 0;
	if (data_program->total_phil < 2 || data_program->total_phil > 200)
	{
		printf("data_program->total_phil: %d\n", data_program->total_phil);
		count += printf("Error: number of philosophers must be between 2-2\n");
	}
	else if (data_program->time_to_die < 60
		|| data_program->time_to_die > INT_MAX)
	{
		printf("data_program->time_to_die: %lld\n", data_program->time_to_die);
		count += printf("Error: time to die must be at least 60\n");
	}
	else if (data_program->time_to_eat < 60
		|| data_program->time_to_eat > INT_MAX)
	{
		printf("data_program->time_to_eat: %lld\n", data_program->time_to_eat);
		count += printf("Error: time to eat must be at least 60\n");
	}
	else if (data_program->time_to_sleep < 60
		|| data_program->time_to_sleep > INT_MAX)
	{
		printf("data_program->time_to_sleep: %lld\n", data_program->time_to_sleep);
		count += printf("Error: time to sleep must be at least 60\n");
	}
	else if (data_program->min_must_eat != -1)
	{
		if (data_program->min_must_eat < 0
			|| data_program->min_must_eat > INT_MAX)
			count += printf("Error: number of times each philosopher must eat must be at least 0\n");
	}
	if (count)
		return (0);
	return (1);
}

int	checker_args(int argc, char *argv[])
{
	int	i;
	int	fails;

	i = 1;
	fails = 0;
	if ((argc < 5 || argc > 6) && argc != 2)
		print_usage();
	while (argv[i])
	{
		if (!ft_isnum(argv[i]))
			fails += printf("%s is not a valid param\n", argv[i]);
		i++;
	}
	if (fails)
		return (0);
	return (1);
}

static int	parse_args(char **argv, t_program *p)
{
	long long	v;

	if (!ft_atoll_safe(argv[1], &v) || v < 1)
		return (0);
	p->total_phil = (int)v;
	if (!ft_atoll_safe(argv[2], &p->time_to_die))
		return (0);
	if (!ft_atoll_safe(argv[3], &p->time_to_eat))
		return (0);
	if (!ft_atoll_safe(argv[4], &p->time_to_sleep))
		return (0);
	p->min_must_eat = -1;
	if (argv[5] && (!ft_atoll_safe(argv[5],
				&p->min_must_eat) || p->min_must_eat < 1))
		return (0);
	return (1);
}

static t_philosopher	*create_philosophers(t_program *p)
{
	t_philosopher	*ph;
	int				i;

	i = 0;
	ph = malloc(sizeof(*ph) * p->total_phil);
	if (!ph)
		return (NULL);
	while (i < p->total_phil)
	{
		ph[i].id = i + 1;
		ph[i].eat_count = 0;
		ph[i].last_eat = 0;
		ph[i].program = p;
		ph[i].last_eat_mutex = (pthread_mutex_t){0};
		ph[i].eat_count_mutex = (pthread_mutex_t){0};
		i++;
	}
	return (ph);
}

t_program	*initial_data(char **argv)
{
	t_program	*data_program;

	data_program = malloc(sizeof(t_program));
	if (!data_program)
		return (NULL);
	if (!parse_args(argv, data_program))
		return (free(data_program), NULL);
	data_program->start_time = get_time_ms();
	data_program->philosophers = create_philosophers(data_program);
	return (data_program);
}

// t_program	*initial_data(char *argv[])
// {
// 	t_program	*data_program;
// 	int			i;

// 	data_program = malloc(sizeof(t_program));
// 	if (!data_program)
// 		close_program(data_program, 1);
// 	data_program->min_must_eat = -1;
// 	i = 0;
// 	while (argv[++i])
// 	{
// 		if (i == 1)
// 			data_program->total_phil = ft_atolli(argv[i]);
// 		else if (i == 2)
// 			data_program->time_to_die = ft_atolli(argv[i]);
// 		else if (i == 3)
// 			data_program->time_to_eat = ft_atolli(argv[i]);
// 		else if (i == 4)
// 			data_program->time_to_sleep = ft_atolli(argv[i]);
// 		else if (i == 5)
// 			data_program->min_must_eat = ft_atolli(argv[i]);
// 	}
// 	data_program->start_time = get_time_ms();
// 	data_program->is_over = 0;
// 	data_program->philosophers = create_philosophers(data_program);
// 	return (data_program);
// }
