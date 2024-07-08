/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_array_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 10:17:30 by rpambhar          #+#    #+#             */
/*   Updated: 2024/07/08 13:44:36 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**duplicate_string_array(char **array, int size)
{
	char	**dup_array;
	int		len;
	int		i;

	if (!array)
		return (NULL);
	len = size;
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
