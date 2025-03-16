/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:37:32 by kegonza           #+#    #+#             */
/*   Updated: 2025/03/16 00:04:02 by kegonza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include "philosophers.h"
# include <semaphore.h>

typedef struct t_philosopher
{
	int					id;
	int					left_fork;
	int					right_fork;
	int					eat_count;
	long long int		last_eat;
	pthread_t			thread;
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
	int				is_dead;
	pthread_mutex_t	is_dead_mutex;
	pthread_mutex_t	*forks;
	pthread_mutex_t	printer;
	t_philosopher	*philosophers;
}	t_program;

#endif
