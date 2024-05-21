/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 16:13:33 by fnikzad           #+#    #+#             */
/*   Updated: 2024/05/21 13:39:20 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	find_vertical(t_cub *game)
// {
// 	int		ys;
// 	int		xs;
// 	float	xn;
// 	float	yn;

// 	xs = game->block_size - 1;
// 	ys = xs / tan(game->ray.ra);
// 	xn = game->block_size - (game->player->px / game->block_size) * game->block_size;
// 	yn = xn * tan(game->ray.ra);
// 	if (game->ray.ra < M_2_PI || game->ray.ra > 3 * M_2_PI)
// 	{
// 		xn = game->player->px + (game->block_size - fmod(game->player->px, game->block_size));
// 		xs = game->block_size;
// 	}
// 	else
// 	{
// 		xn = game->player->px - fmod(game->player->px, game->block_size);
// 		xs = -game->block_size;
// 	}
// 	ys = xs * tan(game->ray.ra);
// 	yn = game->player->py + (xn - game->player->px) * tan(game->ray.ra);
// 	while (xn >= 0 && xn < game->data->map_width * game->block_size &&
// 			yn >= 0 && yn < game->data->map_height * game->block_size)
// 	{
// 		int mapX = (int)(xn / game->block_size);
// 		int mapY = (int)(yn / game->block_size);
		
// 		if (mapX >= 0 && mapX < game->data->map_width && mapY >= 0 && mapY < game->data->map_height)
// 		{
// 			if (game->data->map[mapY][mapX] == '1')
// 			{
// 				game->ray.dis_v = hypot(game->player->px - xn, game->player->py - yn);
// 				game->ray.rx = xn;
// 				game->ray.ry = yn;
// 				break;
// 			}
// 			else
// 			{
// 				xn += xs;
// 				yn += ys;
// 				game->ray.rx = xn;
// 				game->ray.ry = yn;
// 			}
// 		}
// 		else
// 			break;
// 	}
// 	game->ray.vx = xn;
// 	game->ray.vy = yn;
// }


// void	find_horizontal(t_cub *game)
// {
// 	int		ys;
// 	int		xs;
// 	float	xn;
// 	float	yn;

// 	ys = game->block_size;
// 	xs = ys / tan(game->ray.ra);
// 	yn = game->player->py - (game->player->py / game->block_size) * game->block_size;
// 	xn = yn / tan(game->ray.ra);
// 	if (game->ray.ra < M_PI)
// 	{
// 		yn = game->player->py + (game->block_size - fmod(game->player->py , game->block_size));
// 		ys = game->block_size;
// 		xs = ys / tan(game->ray.ra);
// 	}

// 	else
// 	{
// 		yn = game->player->py - fmod(game->player->py , game->block_size);
// 		ys = -game->block_size - 1;
// 		xs = ys / tan(game->ray.ra);
// 	}
// 	xn = game->player->px + (yn - game->player->py) / tan(game->ray.ra);

// 	while (xn >= 0 && xn < game->data->map_width * game->block_size &&
// 			yn >= 0 && yn < game->data->map_height * game->block_size)
// 	{
// 		int mapX = (int)(xn / game->block_size);
// 		int mapY = (int)(yn / game->block_size);
		
// 		if (mapX >= 0 && mapX < game->data->map_width && mapY >= 0 && mapY < game->data->map_height)
// 		{
// 			if (game->data->map[mapY][mapX] == '1')
// 			{
// 				game->ray.rx = xn;
// 				game->ray.ry = yn;
// 				game->ray.dis_h = hypot(game->player->px - xn, game->player->py - yn);
// 				break;
// 			}
// 			else
// 			{
// 				xn += xs;
// 				yn += ys;
// 				game->ray.rx = xn;
// 				game->ray.ry = yn;
// 			}
// 		}
// 		else
// 			break;
// 	}
// 	game->ray.hx = xn;
// 	game->ray.hy = yn;
// }

// void cast_rays(t_cub *game)
// {
// 	int num_rays = 60;
// 	float angle_step = (M_PI / 3) / num_rays;
	
// 	game->ray.ra = game->player->p_a - (M_PI / 6);
	
// 	for (int i = 0; i < num_rays; i++)
// 	{
// 		if (game->ray.ra < 0)
// 			game->ray.ra += 2 * M_PI;
// 		if (game->ray.ra > 2 * M_PI)
// 			game->ray.ra -= 2 * M_PI;
// 		find_horizontal(game);
// 		find_vertical(game);
// 		if (game->ray.dis_h < game->ray.dis_v)
// 		{
// 			game->ray.rx = game->ray.hx;
// 			game->ray.ry = game->ray.hy;
// 		}
// 		else
// 		{
// 			game->ray.rx = game->ray.vx;
// 			game->ray.ry = game->ray.vy;
// 		}
// 		mlx_draw_line(game, 1);
// 		game->ray.ra += angle_step;
// 	}
// }
