/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:32:56 by kev               #+#    #+#             */
/*   Updated: 2025/03/20 01:35:05 by kegonza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"

int	main(int argc, char *argv[])
{
	t_program	*data_program;

	if (argc == 2)
		argv = ft_split_for_apps(argv[0], argv[1], ' ');
	if (!checker_args(argc, argv))
		close_program(NULL, 1);
	data_program = initial_data(argv);
	if (!data_program)
		close_program(data_program, 1);
	if (!check_params(data_program))
		close_program(data_program, 1);
	print_data(data_program);
	init_mutex(data_program);
	printf("mutex done\n");
	// init_thread(data_program->philosophers, data_program);
	// printf("thread done\n");
	usleep(1000);
	close_program(data_program, 0);
	return (0);
}
