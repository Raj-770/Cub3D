/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:00:55 by rpambhar          #+#    #+#             */
/*   Updated: 2024/07/06 14:12:09 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_character(t_map_data *data, int i, int j, int *player_count);
static int	check_for_openings(t_map_data *data);
static int	check_open_lines(t_map_data *data);
static int	check_for_opeings_helper(int i, int j, int len, t_map_data *data);

int	check_map_rules(t_map_data *data)
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
	if (!check_for_openings(data))
		return (0);
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

static int	check_for_openings(t_map_data *data)
{
	int	i;
	int	j;
	int	len;

	i = -1;
	if (!check_open_lines(data))
		return (put_error("The map has openings", 0));
	while (++i < data->map_height)
	{
		j = -1;
		len = ft_strlen(data->map[i]);
		while (++j < len)
		{
			if (!check_for_opeings_helper(i, j, len, data))
				return (put_error("The map has an opening", 0));
		}
	}
	return (1);
}

static int	check_for_opeings_helper(int i, int j, int len, t_map_data *data)
{
	if (data->map[i][j] == '0')
	{
		if (i == 0 || j >= ft_strlen(data->map[i - 1]) || \
		data->map[i - 1][j] == ' ' || data->map[i - 1][j] == '\0')
			return (0);
		if (i == data->map_height - 1 || j >= ft_strlen(data->map[i + 1]) \
		|| data->map[i + 1][j] == ' ' || data->map[i + 1][j] == '\0')
			return (0);
		if (j == 0 || data->map[i][j - 1] == ' ' \
		|| data->map[i][j - 1] == '\0')
			return (0);
		if (j == len - 1 || data->map[i][j + 1] == ' ' \
		|| data->map[i][j + 1] == '\0')
			return (0);
	}
	return (1);
}

static int	check_open_lines(t_map_data *data)
{
	char	*trimed_line;
	int		i;
	int		len;

	i = 0;
	while (i < data->map_height)
	{
		len = ft_strlen(data->map[i]);
		if (data->map_width < len)
			data->map_width = len;
		trimed_line = ft_strtrim(data->map[i], " ");
		if (!(trimed_line[0] == '1') || \
		!(trimed_line[ft_strlen(trimed_line) - 1] == '1'))
		{
			free(trimed_line);
			return (0);
		}
		free(trimed_line);
		i++;
	}
	return (1);
}
