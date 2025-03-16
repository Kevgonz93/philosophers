/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closep.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 00:44:56 by kegonza           #+#    #+#             */
/*   Updated: 2025/03/16 00:55:30 by kegonza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/philosophers.h"

void	close_program(t_program *data_program)
{
	if (data_program)
	{
		destroy_mutex(data_program);
		if (data_program->philosophers)
			free(data_program->philosophers);
		free(data_program);
	}
}
