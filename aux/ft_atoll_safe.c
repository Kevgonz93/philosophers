/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll_safe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonzal <kegonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 12:01:33 by kegonza           #+#    #+#             */
/*   Updated: 2025/08/11 14:28:37 by kegonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

static void	finish_atoll(long long *out, long long val, long long sing)
{
	*out = val * sing;
}

int	ft_atoll_safe(const char *s, long long *out)
{
	long long	sign;
	long long	val;

	sign = 1;
	val = 0;
	if (!s || !*s)
		return (0);
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	if (!*s)
		return (0);
	while (*s >= '0' && *s <= '9')
	{
		val = val * 10 + (*s - '0');
		if (val < 0)
			return (0);
		s++;
	}
	if (*s)
		return (0);
	return (finish_atoll(out, val, sign), 1);
}
