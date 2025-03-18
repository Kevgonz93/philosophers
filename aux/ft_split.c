/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:23:46 by kegonza           #+#    #+#             */
/*   Updated: 2025/03/18 17:12:21 by kegonza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/aux.h"

int	count_words(char *str, char c)
{
	int	words;
	int	i;

	words = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			words++;
			while (str[i] && str[i] != c)
				i++;
		}
		else
			i++;
	}
	return (words);
}

int	count_chars(char *str, char c)
{
	int	chars;
	int	i;

	chars = 0;
	i = 0;
	while (str[i] && str[i] != c)
	{
		chars++;
		i++;
	}
	return (chars);
}

char	*put_name_prog(char *name_pro)
{
	int		i;
	int		size;
	char	*name;

	size = ft_strlen(name_pro);
	name = (char *)malloc(sizeof(char) * (size + 1));
	if (!name)
		return (NULL);
	i = 0;
	while (name_pro[i])
	{
		name[i] = name_pro[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}

char	**ft_split_for_apps(char *name_pro, char *args, char c)
{
	int		words;
	int		chars;
	char	**result;
	int		i;
	int		j;
	int		k;

	words = count_words(args, c);
	result = (char **)malloc(sizeof(char *) * (words + 2));
	if (!result)
		return (NULL);
	result[0] = put_name_prog(name_pro);
	i = 0;
	j = 1;
	while (args[i])
	{
		if (args[i] != c)
		{
			chars = count_chars(&args[i], c);
			result[j] = (char *)malloc(sizeof(char) * (chars + 1));
			if (!result[j])
				return (NULL);
			k = 0;
			while (args[i] && args[i] != c)
			{
				result[j][k] = args[i];
				k++;
				i++;
			}
			result[j][chars] = '\0';
			j++;
		}
		else
			i++;
	}
	result[j] = NULL;
	return (result);
}
