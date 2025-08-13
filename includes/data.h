/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonzal <kegonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:37:32 by kegonza           #+#    #+#             */
/*   Updated: 2025/08/13 11:21:24 by kegonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include "philosophers.h"
# include <semaphore.h>

typedef struct s_program	t_program;

typedef struct s_philosopher
{
	int				id;
	long long		last_eat;
	int				eat_count;
	pthread_t		thread;
	pthread_mutex_t	last_eat_mutex;
	pthread_mutex_t	eat_count_mutex;
	t_program		*program;
}	t_philosopher;

struct s_program
{
	int				total_phil;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		min_must_eat;
	long long		start_time;
	long long		margin;
	int				is_over;
	pthread_mutex_t	printer;
	int				printer_init;
	pthread_mutex_t	isover_mutex;
	int				isover_init;
	pthread_mutex_t	*forks;
	int				forks_init;
	pthread_t		monitor;
	t_philosopher	*philosophers;
};

#endif
