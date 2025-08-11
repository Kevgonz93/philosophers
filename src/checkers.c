/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonzal <kegonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 14:00:50 by kegonzal          #+#    #+#             */
/*   Updated: 2025/08/11 14:55:29 by kegonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	aux_check_params(char *mssg)
{
	if (ft_strcmp(mssg, "NUM_PHILOS"))
		return (printf("Error: number of philosophers invalid\n"));
	if (ft_strcmp(mssg, "DIE_TIME"))
		return (printf("Error: time to die invalid\n"));
	if (ft_strcmp(mssg, "EAT_TIME"))
		return (printf("Error: time to eat invalid\n"));
	if (ft_strcmp(mssg, "SLEEP_TIME"))
		return (printf("Error: time to sleep invalid\n"));
	if (ft_strcmp(mssg, "MUST_EAT"))
		return (printf ("Error: times each philo must eat invalid\n"));
	return (0);
}

int	check_params(t_program *data_program)
{
	int	count;

	count = 0;
	if (data_program->total_phil < 2 || data_program->total_phil > 200)
		count = aux_check_params("NUM_PHILOS");
	else if (data_program->time_to_die < 60
		|| data_program->time_to_die > INT_MAX)
		count += aux_check_params("DIE_TIME");
	else if (data_program->time_to_eat < 60
		|| data_program->time_to_eat > INT_MAX)
		count += aux_check_params("EAT_TIME");
	else if (data_program->time_to_sleep < 60
		|| data_program->time_to_sleep > INT_MAX)
		count += aux_check_params("SLEEP_TIME");
	else if (data_program->min_must_eat != -1)
	{
		if (data_program->min_must_eat < 0
			|| data_program->min_must_eat > INT_MAX)
			count += aux_check_params("MUST_EAT");
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
