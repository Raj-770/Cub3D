/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:32:46 by fnikzad           #+#    #+#             */
/*   Updated: 2024/05/24 17:34:12 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_map_data(t_map_data *data)
{
	data->c_color = 0;
	data->f_color = 0;
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

void	display(t_cub *game)
{
	game->mlx_img = mlx_new_image(game->mlx_ptr, WIDTH, HEIGHT);
	mlx_image_to_window(game->mlx_ptr, game->mlx_img, 0, 0);
}

void	init(t_cub *game)
{
	game->player = malloc(sizeof(t_player));

	game->block_size = calculate_block_size(WIDTH, HEIGHT, \
	game->data->map_width, game->data->map_height);
	// game->block_size /= 3;
	game->player->px = (game->data->start_px * game->block_size) + (game->block_size) / 2;
	game->player->py = (game->data->start_py * game->block_size) + (game->block_size) / 2;
	game->player->pdx = cos(game->player->p_a) * 3;
	game->player->pdy = sin (game->player->p_a) * 3;
	game->mlx_ptr = mlx_init(WIDTH, HEIGHT, "cub3d", true);
}
