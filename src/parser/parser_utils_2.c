/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:38:04 by rpambhar          #+#    #+#             */
/*   Updated: 2024/07/08 13:26:06 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	**ft_realloc_map(char **map, t_parser *parser);

int	add_line_to_map(char *line, t_map_data *data, t_parser *parser)
{
	if (ft_strlen(line) == 0)
		return (1);
	if (!data->map)
	{
		data->map = (char **)malloc(sizeof(char *) * parser->map_capacity);
		if (!data->map)
			return (0);
		parser->map_size = 0;
	}
	if (parser->map_size >= parser->map_capacity)
	{
		data->map = ft_realloc_map(data->map, parser);
		if (!data->map)
			return (0);
	}
	data->map[parser->map_size] = ft_strdup(line);
	if (!data->map[parser->map_size])
		return (0);
	parser->map_size++;
	data->map_height = parser->map_size;
	return (1);
}

static char	**ft_realloc_map(char **map, t_parser *parser)
{
	int		new_size;
	char	**new_map;
	int		i;

	new_size = parser->map_capacity + 10;
	new_map = (char **)malloc(sizeof(char *) * new_size);
	if (!new_map)
		return (NULL);
	i = 0;
	while (i < parser->map_capacity)
	{
		new_map[i] = map[i];
		i++;
	}
	parser->map_capacity += 10;
	free(map);
	return (new_map);
}

void	trim_map(t_map_data *data)
{
	int	start;
	int	end;
	int	new_length;
	int	i;

	start = 0;
	end = data->map_height - 1;
	while (start <= end && data->map[start][0] == '\0')
		start++;
	while (end >= start && data->map[end][0] == '\0')
		end--;
	new_length = end - start + 1;
	if (start > 0 && new_length)
	{
		i = 0;
		while (i < new_length)
		{
			data->map[i] = data->map[start + i];
			i++;
		}
	}
	i = new_length - 1;
	while (++i < data->map_height)
		data->map[i] = NULL;
	data->map_height = new_length;
}
