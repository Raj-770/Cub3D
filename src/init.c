/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:32:46 by fnikzad           #+#    #+#             */
/*   Updated: 2024/05/16 15:13:38 by rpambhar         ###   ########.fr       */
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

void	initialize_parser(t_parser *parser)
{
	parser->line = NULL;
	parser->trimed_line = NULL;
	parser->inside_map = 0;
	parser->map_capacity = 10;
	parser->map_size = 0;
}

//
void	display(t_cub *game)
{
	game->mlx_img = mlx_new_image(game->mlx_ptr, WIDTH, HEIGHT);
	mlx_image_to_window(game->mlx_ptr, game->mlx_img, 0, 0);
}

void	init(t_cub *game)
{
	game->player = malloc(sizeof(t_player));
	game->player->px = (game->data->start_px * 64) - 32;
	game->player->py = (game->data->start_py * 64) - 32;
	game->player->pdx = cos(game->player->p_a) * 5;
	game->player->pdy = sin (game->player->p_a) * 5;
	game->mlx_ptr = mlx_init(WIDTH, HEIGHT, "cub3d", true);
}

double FixAng(double ang) {
	if (ang > (2 * PI))
		ang -= (2 * PI);
	if (ang < 0)
		ang += (2 * PI);
	return ang;
}


void ft_hook(void *param)
{
	t_cub *game = param;

	if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx_ptr);
	game->player->pdx = cos(game->player->p_a);
	game->player->pdy = sin(game->player->p_a);
	if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_A))
	{
		game->player->p_a -= 0.1;
		game->player->p_a = FixAng(game->player->p_a);
		game->player->pdx = cos(game->player->p_a);
		game->player->pdy = sin(game->player->p_a);
	}
	if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_D))
	{
		game->player->p_a += 0.1;
		game->player->p_a = FixAng(game->player->p_a);
		game->player->pdx = cos(game->player->p_a);
		game->player->pdy = sin(game->player->p_a);
	}
	if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_W))
	{
		game->player->px += game->player->pdx * 5;
		game->player->py += game->player->pdy * 5;
	}
	if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_S))
	{
		game->player->px -= game->player->pdx * 5;
		game->player->py -= game->player->pdy * 5;
	}
}
