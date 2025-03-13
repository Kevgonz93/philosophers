#ifndef DATA_H
# define DATA_H

# include <semaphore.h>

typedef struct t_philosopher
{
	int					id;
	int					left_fork;
	int					right_fork;
	int					eat_count;
	long long			last_eat;
	pthread_t			thread;
	t_program			*data_program;
}	t_philosopher;

typedef struct t_program
{
	int				total_phil;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				min_must_eat;
	long long		start_time;
	int				dead;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	t_philosopher	*philosophers;
}	t_program;

#endif
