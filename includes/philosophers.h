/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonzal <kegonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:37:22 by kegonza           #+#    #+#             */
/*   Updated: 2025/08/13 11:30:21 by kegonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "aux.h"
# include "data.h"
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>

// ACTIONS.C

void			*to_sleep(t_philosopher *philosopher);
void			*to_think(t_philosopher *philosopher);
void			*to_eat(t_philosopher *philosopher);
void			*routine(void *arg);

// CHECKERS.C

int				check_params(t_program *data_program);
int				checker_args(int argc, char *argv[]);

// CLOSEP.C

int				close_program(t_program *p, int fail);

// FORKS.C

void			lock_both_forks(t_philosopher *ph, int left, int right);
void			unlock_both_forks(t_philosopher *ph, int left, int right);

// INITIAL SETTINGS

t_program		*initial_data(char **argv);
void			set_initial_time(t_program *data);

// UTILS.C

long long		get_time_ms(void);
void			printer(t_philosopher *philosopher, char *str);
void			print_data(t_program *data_program);
int				print_usage(void);
long long		get_margin(t_program *data_program);

// MUTEX.C

void			init_mutex(t_program *data_program);
void			destroy_mutex(t_program *data_program);

// PHILOSOPHERS.C

int				has_died(t_philosopher *philosopher);
void			*monitor(void *arg);
void			init_thread(t_philosopher *ph, t_program *p);
void			finish_thread(t_program *p);

#endif
