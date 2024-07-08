/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:32:46 by fnikzad           #+#    #+#             */
/*   Updated: 2024/07/08 13:11:23 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_map_data(t_map_data *data)
{
	data->c_color = -1;
	data->f_color = -1;
	data->map = NULL;
	data->map_height = 0;
	data->start_px = 0;
	data->start_py = 0;
	data->no_tex = NULL;
	data->so_tex = NULL;
	data->ea_tex = NULL;
	data->we_tex = NULL;
	data->map_width = 0;
}

static void	initialize_identifiers(t_id *identifiers)
{
	identifiers[0] = (t_id){"NO ", 3, 0};
	identifiers[1] = (t_id){"SO ", 3, 0};
	identifiers[2] = (t_id){"EA ", 3, 0};
	identifiers[3] = (t_id){"WE ", 3, 0};
	identifiers[4] = (t_id){"C ", 2, 0};
	identifiers[5] = (t_id){"F ", 2, 0};
}

void	initialize_parser(t_parser *parser)
{
	parser->line = NULL;
	parser->trimed_line = NULL;
	parser->inside_map = 0;
	parser->map_capacity = 10;
	parser->map_size = 0;
	initialize_identifiers(parser->identifiers);
}

void	init_game_data(t_cub *game, t_map_data *data)
{
	game->data = data;
	game->player = malloc(sizeof(t_player));
	game->player->p_a = data->player_angle;
	game->block_size = calculate_block_size(WIDTH, HEIGHT, \
	game->data->map_width, game->data->map_height);
	game->player->px = (game->data->start_px * game->block_size) + \
	(game->block_size) / 2;
	game->player->py = (game->data->start_py * game->block_size) + \
	(game->block_size) / 2;
	game->mlx_ptr = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	game->mlx_img = mlx_new_image(game->mlx_ptr, WIDTH, HEIGHT);
	mlx_image_to_window(game->mlx_ptr, game->mlx_img, 0, 0);
}

void	init_tex_data(t_texture *tex_data, t_cub *game, mlx_texture_t *tex, \
t_v_line line)
{
	tex_data->deltax = line.end_x - line.begin_x;
	tex_data->deltay = line.end_y - line.begin_y;
	tex_data->pixels = (int)sqrt((tex_data->deltax * tex_data->deltax) + \
	(tex_data->deltay * tex_data->deltay));
	tex_data->pixelx = line.begin_x;
	tex_data->pixely = line.begin_y;
	tex_data->deltax /= tex_data->pixels;
	tex_data->deltay /= tex_data->pixels;
	if (game->ray.side_flag == 1)
		tex_data->wall_hit_x = game->ray.rx;
	else
		tex_data->wall_hit_x = game->ray.ry;
	tex_data->texture_x = (tex_data->wall_hit_x - (int)(tex_data->wall_hit_x / \
	game->block_size) * game->block_size) / game->block_size * tex->width;
	if (line.end_y - line.begin_y != 0)
		tex_data->texture_step = (double)tex->height / \
		(line.end_y - line.begin_y);
	tex_data->texture_pos = 0;
}
