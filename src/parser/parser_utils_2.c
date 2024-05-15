/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:38:04 by rpambhar          #+#    #+#             */
/*   Updated: 2024/05/15 13:17:07 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	add_line_to_map(char *line, t_map_data *data, t_parser *parser);
static char	**ft_realloc_map(char **map, t_parser *parser);

int	parse_map_line(char *line, t_map_data *data, t_parser *parser)
{
	parser->inside_map = 1;
	add_line_to_map(line, data, parser);
	return (1);
}

static int	add_line_to_map(char *line, t_map_data *data, t_parser *parser)
{
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
	data->map_size = parser->map_size;
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
	// free(map);
	parser->map_capacity += 10;
	return (new_map);
}