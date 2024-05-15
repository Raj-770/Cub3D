/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:01:21 by rpambhar          #+#    #+#             */
/*   Updated: 2024/05/15 15:02:46 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_map_data(t_map_data *data)
{
	data->c_color = 0;
	data->f_color = 0;
	data->map = NULL;
	data->map_size = 0;
	data->start_px = 0;
	data->start_py = 0;
	data->no_tex = NULL;
	data->so_tex = NULL;
	data->ea_tex = NULL;
	data->we_tex = NULL;
}

void	initialize_parser(t_parser *parser)
{
	parser->line = NULL;
	parser->trimed_line = NULL;
	parser->inside_map = 0;
	parser->map_capacity = 10;
	parser->map_size = 0;
}

