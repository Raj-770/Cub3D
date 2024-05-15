/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:18:00 by rpambhar          #+#    #+#             */
/*   Updated: 2024/05/15 12:36:44 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct s_id
{
	const char	*prefix;
	size_t		length;
}	t_id;

static int	parse_textures_and_colors(char *line, t_id *id, t_map_data *data);
static int	parse_color(char *line, t_id *id, t_map_data *data);
static void	initialize_identifiers(t_id *identifiers);

int	parse_map_file_line(char *line, t_map_data *data, t_parser *parser)
{
	t_id	identifiers[6];
	int		i;

	initialize_identifiers(identifiers);
	i = 0;
	while (i < 6)
	{
		if (ft_strncmp(line, identifiers[i].prefix, identifiers[i].length) == 0)
		{
			if (!parse_textures_and_colors(line, &identifiers[i], data))
				return (0);
			return (1);
		}
		i++;
	}
	if (line[0] == '\0' && !parser->inside_map)
		return (1);
	else if (line[0] == '\0' && parser->inside_map)
		return (put_error("Empty Line inside map", 0));
	else
		return (parse_map_line(line, data, parser));
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
		return (free_array(color_array), put_error("Invalid Color Format", 0));
	r = atoi(color_array[0]);
	g = atoi(color_array[1]);
	b = atoi(color_array[2]);
	free_array(color_array);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (put_error("Color values out of range", 0));
	color = (r << 16) | (g << 8) | b;
	if (ft_strcmp(id->prefix, "C ") == 0)
		data->c_color = color;
	else if (ft_strcmp(id->prefix, "F ") == 0)
		data->f_color = color;
	return (1);
}

static void	initialize_identifiers(t_id *identifiers)
{
	identifiers[0] = (t_id){"NO ", 3};
	identifiers[1] = (t_id){"SO ", 3};
	identifiers[2] = (t_id){"EA ", 3};
	identifiers[3] = (t_id){"WE ", 3};
	identifiers[4] = (t_id){"C ", 2};
	identifiers[5] = (t_id){"F ", 2};
}
