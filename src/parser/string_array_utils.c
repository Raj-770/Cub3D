/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_array_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 10:17:30 by rpambhar          #+#    #+#             */
/*   Updated: 2024/07/08 10:17:49 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**duplicate_string_array(char **array)
{
	char	**dup_array;
	int		len;
	int		i;

	if (!array)
		return (NULL);
	len = string_array_length(array);
	dup_array = ft_calloc(1, (len + 1) * sizeof(char *));
	if (!dup_array)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup_array[i] = ft_strdup(array[i]);
		if (!dup_array[i])
		{
			free_string_array(dup_array);
			return (NULL);
		}
		i++;
	}
	return (dup_array);
}

void	free_string_array(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
}

int	string_array_length(char **array)
{
	int	length;

	length = 0;
	while (array[length] != NULL)
		length++;
	return (length);
}
