/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:32:56 by kev               #+#    #+#             */
/*   Updated: 2025/08/11 11:52:46 by kegonza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"

int	main(int argc, char **argv)
{
	t_program	*p;

	if (!checker_args(argc, argv))
		return (print_usage());
	p = initial_data(argv);
	if (!p || !check_params(p))
		return (close_program(p, 1));
	init_mutex(p);
	init_thread(p->philosophers, p);
	finish_thread(p);
	return (close_program(p, 0));
}
