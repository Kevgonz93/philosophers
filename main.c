/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:32:56 by kev               #+#    #+#             */
/*   Updated: 2025/03/16 00:53:59 by kegonza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"

int	main(int argc, char *argv[])
{
	t_program	*data_program;

	if (!checker_args(argc, argv))
		exit (1);
	data_program = initial_data(argc, argv);
	if (!data_program)
		return (1);
	if (!check_params(data_program))
	{
		close_program(data_program);
		return (1);
	}
	print_data(data_program);
	init_mutex(data_program);
	init_thread(data_program->philosophers, data_program);
	close_program(data_program);
	return (0);
}
