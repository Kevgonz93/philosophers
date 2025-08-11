/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll_safe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 12:01:33 by kegonza           #+#    #+#             */
/*   Updated: 2025/08/11 12:02:52 by kegonza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	*out = val * sign;
	return (1);
}
