/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closep.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonzal <kegonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 00:44:56 by kegonza           #+#    #+#             */
/*   Updated: 2025/08/11 13:43:09 by kegonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	close_program(t_program *p, int fail)
{
	if (p)
	{
		destroy_mutex(p);
		free(p->forks);
		free(p->philosophers);
		free(p);
	}
	if (fail)
		return (1);
	return (0);
}
