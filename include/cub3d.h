/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 16:26:50 by rpambhar          #+#    #+#             */
/*   Updated: 2024/05/15 15:05:12 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <math.h>
# include <libft.h>
# include <MLX42.h>
# include <get_next_line.h>

typedef struct s_map_data
{
	char	**map;
	char	*no_tex;
	char	*ea_tex;
	char	*so_tex;
	char	*we_tex;
	int		c_color;
	int		f_color;
	int		start_px;
	int		start_py;
	int		map_size;
}	t_map_data;

typedef struct s_parser
{
	char	*line;
	char	*trimed_line;
	int		fd;
	int		inside_map;
	int		map_size;
	int		map_capacity;
}	t_parser;

// Parser
int		parser(int argc, char **argv, t_map_data *data);
int		parse_map_file_line(char *line, t_map_data *data, t_parser *parser);
int		parse_map_line(char *line, t_map_data *data, t_parser *parser);
int		check_map_rules(t_map_data *data);

// Utils
int		put_error(char *str, int i);
void	free_array(char **array);
void	free_map_data(t_map_data *data);

// Init
void	init_map_data(t_map_data *data);
void	initialize_parser(t_parser *parser);

#endif