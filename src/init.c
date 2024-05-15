/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:32:46 by fnikzad           #+#    #+#             */
/*   Updated: 2024/05/15 14:55:01 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	game->player->px = 20;
	game->player->py = 20;
	
	game->mlx_ptr = mlx_init(1920, 1080, "cub3d", true);
}

void ft_hook(void* param)
{
	t_cub *game;

	game = param;
	if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx_ptr);
	if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_W))
		game->player->py -= 5;
	if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_S))
		game->player->py += 5;
	if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_A))
		game->player->px -= 5;
	if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_D))
		game->player->px += 5;
}
