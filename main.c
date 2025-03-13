#include "philosophers.h"

void	create_philosophers(t_program *data_program)
{
	int	i;

	data_program->philosophers = malloc(sizeof(t_philosopher)
			* data_program->total_phil);
	if (!data_program->philosophers)
	{
		perror("Error: malloc");
		exit(1);
	}
	i = 0;
	while (i < data_program->total_phil)
	{
		data_program->philosophers[i].id = i + 1;
		data_program->philosophers[i].left_fork = i;
		data_program->philosophers[i].right_fork = (i + 1)
			% data_program->total_phil;
		data_program->philosophers[i].eat_count = 0;
		data_program->philosophers[i].last_eat = data_program->start_time;
		data_program->philosophers[i].data_program = data_program;
		if (pthread_create(&data_program->philosophers[i++],
				NULL, &routine, &data_program->philosophers[i]))
		{
			perror("Error: pthread create");
			exit(1);
		}
	}
	i = 0;
	while (i < data_program->total_phil)
	{
		if (pthread_join(data_program->philosophers[i++], NULL))
		{
			perror("Error: pthread join");
			exit(1);
		}
	}
}

void	init_mutex(t_program *data_program)
{
	int	i;

	data_program->forks = malloc(sizeof(pthread_mutex_t)
			* data_program->total_phil);
	if (!data_program->forks)
	{
		perror("Error: malloc");
		exit(1);
	}
	i = 0;
	while (i < data_program->total_phil)
	{
		if (pthread_mutex_init(&data_program->forks[i], NULL))
		{
			perror("Error: mutex init");
			exit(1);
		}
		i++;
	}
	pthread_mutex_init(&data_program->print, NULL);
}

t_program	*initial_data(int argc, char *argv[])
{
	t_program	*data_program;
	int			i;

	data_program = malloc(sizeof(t_program));
	if (!data_program)
	{
		perror("Error: malloc");
		exit(1);
	}
	i = 0;
	while (++i < argc)
	{
		if (i == 1)
			data_program->total_phil = ft_atoi(argv[i]);
		else if (i == 2)
			data_program->time_to_die = ft_atoi(argv[i]);
		else if (i == 3)
			data_program->time_to_eat = ft_atoi(argv[i]);
		else if (i == 4)
			data_program->time_to_sleep = ft_atoi(argv[i]);
		else if (i == 5)
			data_program->min_must_eat = ft_atoi(argv[i]);
	}
	data_program->start_time = get_time();
	return (data_program);
}

int	main(int argc, char *argv[])
{
	t_program	*data_program;

	checker_args(argc, argv);
	data_program = initial_data(argc, argv);
	if (!data_program)
		return (1);
	if (!check_params(data_program))
		close_program(data_program);
	init_mutex(data_program);
	create_philosophers(data_program);
}
