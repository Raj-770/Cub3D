/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:18:00 by rpambhar          #+#    #+#             */
/*   Updated: 2024/07/08 13:27:37 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	parse_textures_and_colors(char *line, t_id *id, t_map_data *data);
static int	parse_color(char *line, t_id *id, t_map_data *data);
static int	found_all_identifiers(t_map_data *data);

int	parse_map_file_line(char *line, t_map_data *data, t_parser *parser)
{
	int		i;
	int		count;
	t_id	*identifier;

	identifier = parser->identifiers;
	i = 0;
	count = 0;
	while (i < 6)
	{
		if (ft_strncmp(line, identifier[i].prefix, identifier[i].length) == 0)
		{
			identifier[i].count++;
			if (identifier[i].count > 1)
				return (put_error("More than expected identifiers Found", 0));
			if (!parse_textures_and_colors(line, &identifier[i], data))
				return (0);
			return (1);
		}
		else
			count++;
		i++;
	}
	if (count == 6 && !found_all_identifiers(data) && ft_strlen(line) != 0)
		return (put_error("Identifiers not found", 0));
	return (add_line_to_map(line, data, parser));
}

static int	found_all_identifiers(t_map_data *data)
{
	if (data->c_color == -1 || data->f_color == -1 || !data->no_tex \
	|| !data->so_tex || !data->ea_tex || !data->we_tex)
		return (0);
	return (1);
}

static int	parse_textures_and_colors(char *line, t_id *id, t_map_data *data)
{
	char	*texture_path;

	line += id->length;
	if (id->length == 3)
	{
		texture_path = ft_strtrim(line, " ");
		if (ft_strcmp(id->prefix, "NO ") == 0)
			data->no_tex = texture_path;
		else if (ft_strcmp(id->prefix, "SO ") == 0)
			data->so_tex = texture_path;
		else if (ft_strcmp(id->prefix, "EA ") == 0)
			data->ea_tex = texture_path;
		else if (ft_strcmp(id->prefix, "WE ") == 0)
			data->we_tex = texture_path;
	}
	else if (id->length == 2)
	{
		if (!parse_color(line, id, data))
			return (0);
	}
	return (1);
}

static int	parse_color(char *line, t_id *id, t_map_data *data)
{
	char	**color_array;
	int		r;
	int		g;
	int		b;
	int		color;

	color_array = ft_split(line, ',');
	if (!color_array)
		return (put_error("Error splitting color string", 0));
	if (color_array[3])
		return (free_string_array(color_array), \
		put_error("Invalid Color Format", 0));
	r = atoi(color_array[0]);
	g = atoi(color_array[1]);
	b = atoi(color_array[2]);
	free_string_array(color_array);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (put_error("Color values out of range", 0));
	color = (r << 24) | (g << 16) | b << 8 | 255;
	if (ft_strcmp(id->prefix, "C ") == 0)
		data->c_color = color;
	else if (ft_strcmp(id->prefix, "F ") == 0)
		data->f_color = color;
	return (1);
}
