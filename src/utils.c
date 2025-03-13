#include "philosophers.h"

int	check_params(t_program *data_program)
{
	if (data_program->total_phil < 2)
		printf("Error: number of philosophers must be at least 2\n");
	else if (data_program->time_to_die < 60)
		printf("Error: time to die must be at least 60\n");
	else if (data_program->time_to_eat < 60)
		printf("Error: time to eat must be at least 60\n");
	else if (data_program->time_to_sleep < 60)
		printf("Error: time to sleep must be at least 60\n");
	else if (data_program->min_must_eat < 0)
		printf("Error: number of times each philosopher must eat must be at least 0\n");
	return (1);
}

void	checker_args(int argc, char *argv[])
{
	if (argc != 5 || argc != 6)
	{
		printf("Usage: ./philosophers");
		printf(" number_of_philosophers");
		printf(" time_to_die");
		printf(" time_to_eat");
		printf(" time_to_sleep");
		printf(" number_of_times_each_philosopher_must_eat(optional)\n");
		exit(0);
	}
}

void	close_program(t_program *data_program)
{
	if (data_program->forks)
		free(data_program->forks);
	if (data_program->philosophers)
		free(data_program->philosophers);
	free(data_program);
	exit(1);
}
