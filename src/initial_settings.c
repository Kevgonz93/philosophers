/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial_settings.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonzal <kegonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:57:04 by kegonza           #+#    #+#             */
/*   Updated: 2025/08/11 14:49:57 by kegonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

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

void	set_initial_time(t_program *data)
{
	int				i;

	i = 0;
	while (i < data->total_phil)
	{
		pthread_mutex_lock(&data->philosophers[i].last_eat_mutex);
		data->philosophers[i].last_eat = data->start_time;
		pthread_mutex_unlock(&data->philosophers[i].last_eat_mutex);
		i++;
	}
}
