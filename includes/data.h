/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:37:32 by kegonza           #+#    #+#             */
/*   Updated: 2025/03/20 01:17:57 by kegonza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include "philosophers.h"
# include <semaphore.h>

typedef struct t_philosopher
{
	pthread_t			thread;
	int					id;
	int					left_fork;
	int					right_fork;
	int					eat_count;
	pthread_mutex_t		eat_count_mutex;
	long long int		last_eat;
	pthread_mutex_t		last_eat_mutex;
	struct t_program	*program;
}	t_philosopher;

typedef struct t_program
{
	int				total_phil;
	long long int	time_to_die;
	long long int	time_to_eat;
	long long int	time_to_sleep;
	int				min_must_eat;
	long long int	start_time;
	int				is_over;
	pthread_mutex_t	monitor;
	int				monitor_init;
	pthread_mutex_t	*forks;
	int				forks_init;
	pthread_mutex_t	printer;
	int				printer_init;
	t_philosopher	*philosophers;
}	t_program;

#endif
