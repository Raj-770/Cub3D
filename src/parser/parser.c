/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:22:08 by rpambhar          #+#    #+#             */
/*   Updated: 2024/07/08 13:44:51 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_for_file_extension(char *str);
static int	parse_map_file(char *path, t_map_data *data);
static int	check_identifiers(t_map_data *data);

int	parser(int argc, char **argv, t_map_data *data)
{
	if (argc != 2)
		return (put_error("Invalid Arguments", 0));
	if (!check_for_file_extension(argv[1]))
		return (put_error("Invalid File Extension", 0));
	if (!parse_map_file(argv[1], data))
		return (0);
	if (!convert_images(data))
		return (0);
	return (1);
}

static int	check_for_file_extension(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (len < 4)
		return (0);
	if (ft_strncmp(&str[len - 4], ".cub", 4) == 0)
		return (1);
	return (0);
}

static int	parse_map_file(char *path, t_map_data *data)
{
	t_parser	parser;

	initialize_parser(&parser);
	parser.fd = open(path, O_RDONLY);
	if (parser.fd == -1)
		return (put_error("Unable to open file", 0));
	while (1)
	{
		parser.line = get_next_line(parser.fd);
		if (!parser.line)
			break ;
		parser.trimed_line = ft_strtrim(parser.line, "\n");
		if (!parse_map_file_line(parser.trimed_line, data, &parser))
		{
			close(parser.fd);
			return (free(parser.line), free(parser.trimed_line), 0);
		}
		free(parser.line);
		free(parser.trimed_line);
	}
	if (!check_identifiers(data) || !check_map_rules(data))
		return (0);
	close(parser.fd);
	return (1);
}

static int	check_identifiers(t_map_data *data)
{
	if (data->c_color == -1 || data->f_color == -1 || !data->no_tex \
	|| !data->so_tex || !data->ea_tex || !data->we_tex || !data->map)
		return (put_error("Missing Identifier", 0));
	return (1);
}
