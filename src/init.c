/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:32:46 by fnikzad           #+#    #+#             */
/*   Updated: 2024/05/15 18:37:33 by fnikzad          ###   ########.fr       */
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

// void drawPlayer(void *param)
// {
// 	t_cub	*game;

// 	game = param;
//     int player_size = 8;

//     int x, y;
//     for (x = game->px; x < game->px + player_size; x++)
//     {
//         for (y = game->py; y < game->py + player_size; y++)
//         {
// 			uint32_t color = ft_pixel(255, 255, 0, 255);
//             mlx_put_pixel(game->mlx_img, x, y, color);
//         }
//     }
// }

void	display(t_cub *game)
{
	game->mlx_img = mlx_new_image(game->mlx_ptr, 1920, 1080);
	mlx_image_to_window(game->mlx_ptr, game->mlx_img, 0, 0);
}

void	init(t_cub *game)
{
	game->player = malloc(sizeof(t_player));
	game->player->px = (game->data->start_px * 64) - 32;
	game->player->py = (game->data->start_py * 64) - 32;
	game->player->pdx = cos(game->player->p_a) * 5;
	game->player->pdy = sin (game->player->p_a) * 5;
	game->mlx_ptr = mlx_init(1920, 1080, "cub3d", true);
}




// void ft_hook(void* param)
// {
// 	t_cub *game;

// 	game = param;
// 	if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_ESCAPE))
// 		mlx_close_window(game->mlx_ptr);
// 	if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_W))
// 		game->player->py -= 5;
// 	if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_S))
// 		game->player->py += 5;
// 	if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_A))
// 		game->player->px -= 5;
// 	if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_D))
// 		game->player->px += 5;
// }

// double degToRad(double deg) {
//     return deg * PI / 180.0;
// }

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

    // Rotate left
    if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_A)) {
        game->player->p_a -= 0.1;
        game->player->p_a = FixAng(game->player->p_a);
        game->player->pdx = cos(game->player->p_a);
        game->player->pdy = sin(game->player->p_a);
    }

    // Rotate right
    if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_D)) {
        game->player->p_a += 0.1;
        game->player->p_a = FixAng(game->player->p_a);
        game->player->pdx = cos(game->player->p_a);
        game->player->pdy = sin(game->player->p_a);
    }

    // Move forward
    if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_W)) {
        game->player->px += game->player->pdx * 5;
        game->player->py += game->player->pdy * 5;
    }

    // Move backward
    if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_S)) {
        game->player->px -= game->player->pdx * 5;
        game->player->py -= game->player->pdy * 5;
    }

    // Redraw the map with the updated player position
    // drawMap2D(game);
}
