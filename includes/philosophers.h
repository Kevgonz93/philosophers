/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:37:22 by kegonza           #+#    #+#             */
/*   Updated: 2025/03/16 01:06:19 by kegonza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "aux.h"
# include "data.h"
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>


// INITIAL SETTINGS

int				checker_args(int argc, char *argv[]);
int				check_params(t_program *data_program);
t_program		*initial_data(int argc, char *argv[]);

// UTILS.C

long long		get_time_ms(void);
void			printer(t_philosopher *philosopher, char *str);
void			print_data(t_program *data_program);
void			print_usage(void);

// MUTEX.C

void			init_mutex(t_program *data_program);
void			destroy_mutex(t_program *data_program);

// ACTIONS.C

void			*to_sleep(t_philosopher *philosopher);
void			*to_think(t_philosopher *philosopher);
void			*to_eat(t_philosopher *philosopher);
void			*routine(void *arg);

// CLOSEP.C

void			close_program(t_program *data_program);

// PHILOSOPHERS.C

void			init_thread(t_philosopher *philosophers,
					t_program *data_program);
t_philosopher	*create_philosophers(t_program *data_program);



#endif
