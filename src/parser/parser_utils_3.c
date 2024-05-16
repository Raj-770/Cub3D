/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:00:55 by rpambhar          #+#    #+#             */
/*   Updated: 2024/05/16 15:03:12 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_character(t_map_data *data, int i, int j, int *player_count);
static void	trim_map(t_map_data *data);
static int	check_for_openings(t_map_data *data);
static int	check_open_lines(t_map_data *data);

int	check_map_rules(t_map_data *data)
{
	int	i;
	int	j;
	int	player_count;

	i = 0;
	player_count = 0;
	trim_map(data);
	while (i < data->map_size)
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
	if (!check_for_openings(data))
		return (0);
	return (1);
}

static int	check_character(t_map_data *data, int i, int j, int *player_count)
{
	char c;

	c = data->map[i][j];
	if (!(c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' \
	|| c == 'W' || c == ' '))
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

static void	trim_map(t_map_data *data)
{
	int	start;
	int	end;
	int	new_length;
	int	i;

	start = 0;
	end = data->map_size - 1;
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
	while (++i < data->map_size)
		data->map[i] = NULL;
	data->map_size = new_length;
}

static int	check_for_openings(t_map_data *data)
{
	int i;
	int	j;

	i = -1;
	if (!check_open_lines(data))
		return (put_error("The map has openings", 0));
	while (++i < data->map_size)
	{
		j = -1;
		while (++j < ft_strlen(data->map[i]) - 1)
			if (data->map[i][j] == '0')
				if (i == 0 || i == data->map_size -1 \
				|| data->map[i - 1][j] == ' ' || data->map[i - 1][j] == '\0' \
				|| data->map[i][j - 1] == ' ' || data->map[i][j - 1] == '\0' \
				|| data->map[i + 1][j] == ' ' || data->map[i + 1][j] == '\0' \
				|| data->map[i][j + 1] == ' ' || data->map[i][j + 1] == '\0')
					return (put_error("The map has openings", 0));
	}
	return (1);
}

static int	check_open_lines(t_map_data *data)
{
	char	*trimed_line;
	int		i;

	i = 0;
	while (i < data->map_size)
	{
		trimed_line = ft_strtrim(data->map[i], " ");
		if (!(trimed_line[0] = '1') || !(trimed_line[ft_strlen(trimed_line) - 1] == '1'))
		{
			free(trimed_line);
			return (0);
		}
		i++;
	}
	return (1);
}