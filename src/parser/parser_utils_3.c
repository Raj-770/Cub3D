/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:00:55 by rpambhar          #+#    #+#             */
/*   Updated: 2024/07/08 13:43:25 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_map_characters(t_map_data *data);
static int	check_character(t_map_data *data, int i, int j, int *player_count);
static bool	flood_fill(t_map_data *data, int x, int y, char c);
static void	reset_map(t_map_data *data, char **temp);

int	check_map_rules(t_map_data *data)
{
	char	**dup_map;
	int		i;
	int		len;

	if (!check_map_characters(data))
		return (0);
	dup_map = duplicate_string_array(data->map, data->map_height);
	if (!flood_fill(data, data->start_px, data->start_py, '-'))
	{
		free_string_array(dup_map);
		return (put_error("Invalid Map!", 0));
	}
	reset_map(data, dup_map);
	i = 0;
	while (i < data->map_height)
	{
		len = ft_strlen(data->map[i]);
		if (data->map_width < len)
			data->map_width = len;
		i++;
	}
	free_string_array(dup_map);

	return (1);
}

static int	check_map_characters(t_map_data *data)
{
	int	i;
	int	j;
	int	player_count;

	i = 0;
	player_count = 0;
	trim_map(data);
	while (i < data->map_height)
	{
		j = 0;
		while (data->map[i][j])
		{
			if (!check_character(data, i, j, &player_count))
				return (0);
			j++;
		}
		if (data->map[i][0] == '\0')
			return (put_error("Empty line inside the map", 0));
		i++;
	}
	if (player_count != 1)
		return (put_error("Invalid number of player start position", 0));
	return (1);
}

static int	check_character(t_map_data *data, int i, int j, int *player_count)
{
	char	c;

	c = data->map[i][j];
	if (!(c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' \
	|| c == 'W' || c == ' '))
		return (put_error("Map contains invalid characters", 0));
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		data->start_py = i;
		data->start_px = j;
		data->map[i][j] = '0';
		if (c == 'E')
			data->player_angle = degrees_to_radians(0);
		else if (c == 'N')
			data->player_angle = degrees_to_radians(90);
		else if (c == 'W')
			data->player_angle = degrees_to_radians(180);
		else if (c == 'S')
			data->player_angle = degrees_to_radians(270);
		(*player_count)++;
	}
	return (1);
}

static bool	flood_fill(t_map_data *data, int x, int y, char c)
{
	bool	up;
	bool	down;
	bool	left;
	bool	right;

	if (y < 0 || y >= data->map_height || x < 0 || \
	x >= (int)ft_strlen(data->map[y]))
		return (false);
	if (data->map[y][x] && (data->map[y][x] == '1' || data->map[y][x] == c))
		return (true);
	if (data->map[y][x] && data->map[y][x] == ' ')
		return (false);
	data->map[y][x] = c;
	up = flood_fill(data, x, y - 1, c);
	down = flood_fill(data, x, y + 1, c);
	left = flood_fill(data, x - 1, y, c);
	right = flood_fill(data, x + 1, y, c);
	return (up && down && left && right);
}

static void	reset_map(t_map_data *data, char **temp)
{
	int	i;

	i = 0;
	while (i < data->map_height)
	{
		free(data->map[i]);
		data->map[i] = ft_strdup(temp[i]);
		i++;
	}
}
