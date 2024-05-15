/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:38:04 by rpambhar          #+#    #+#             */
/*   Updated: 2024/05/15 14:58:34 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	add_line_to_map(char *line, t_map_data *data, t_parser *parser);
static char	**ft_realloc_map(char **map, t_parser *parser);
static int	check_character(t_map_data *data, int i, int j, int *player_count);
static int	is_valid_map_char(char c);

int	parse_map_line(char *line, t_map_data *data, t_parser *parser)
{
	parser->inside_map = 1;
	if (!add_line_to_map(line, data, parser))
		return (0);
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
	parser->map_capacity += 10;
	free(map);
	return (new_map);
}

int	check_map_rules(t_map_data *data)
{
	int	i;
	int	j;
	int	player_count;

	i = 0;
	player_count = 0;
	while (i < data->map_size)
	{
		j = 0;
		while (data->map[i][j])
		{
			if (!check_character(data, i, j, &player_count))
				return (0);
			j++;
		}
		i++;
	}
	if (player_count != 1)
		return (put_error("Invalid number of player start position", 0));
	return (1);
}

static int	check_character(t_map_data *data, int i, int j, int *player_count)
{
	char c;

	c = data->map[i][j];
	if (!is_valid_map_char(c))
		return (put_error("Map contains invalid characters", 0));
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		data->start_py = i;
		data->start_px = j;
		data->map[i][j] = '0';
		(*player_count)++;
	}
	return (1);
}

static int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' \
	|| c == 'W' || c == '\0');
}