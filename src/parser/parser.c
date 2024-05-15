/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:22:08 by rpambhar          #+#    #+#             */
/*   Updated: 2024/05/15 12:36:03 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_for_file_extension(char *str);
static int	parse_map_file(char *path, t_map_data *data);
static void	initialize_parser(t_parser *parser);

int	parser(int argc, char **argv, t_map_data *data)
{
	if (argc != 2)
		return (put_error("Invalid Arguments", 0));
	if (!check_for_file_extension(argv[1]))
		return (put_error("Invalid File Extension", 0));
	if (!parse_map_file(argv[1], data))
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
	int		fd;
	char	*line;
	char	*temp;
	t_parser	parser;

	initialize_parser(&parser);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (put_error("Unable to open file", 0));
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		temp = ft_strtrim(line, "\n");
		if (!parse_map_file_line(temp, data, &parser))
		{
			close(fd);
			return (free(line), free(temp), 0);
		}
		free(line);
		free(temp);
	}
	close(fd);
	return (1);
}

static void	initialize_parser(t_parser *parser)
{
	parser->inside_map = 0;
	parser->map_capacity = 10;
	parser->map_size = 0;
}