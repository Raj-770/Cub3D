/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:05:52 by fnikzad           #+#    #+#             */
/*   Updated: 2024/06/23 15:40:40 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	find_horizontal(t_cub *game, float ray_angle)
{
	float	xn;
	float	yn;
	float	xs;
	float	ys;
	int		map_x;
	int		map_y;

	if (ray_angle == 0 || ray_angle == M_PI)
	{
		game->ray.hx = game->player->px;
		game->ray.hy = game->player->py;
		game->ray.dis_h = INFINITY;
		return ;
	}
	if (ray_angle < M_PI)
	{
		yn = game->player->py + (game->block_size - \
		fmod(game->player->py, game->block_size));
		ys = game->block_size;
	}
	else
	{
		yn = game->player->py - fmod(game->player->py, game->block_size);
		ys = -(game->block_size);
	}
	xs = ys / tan(ray_angle);
	xn = game->player->px + (yn - game->player->py) / tan(ray_angle);
	while (xn >= 0 && xn < game->data->map_width * game->block_size && \
	yn >= 0 && yn < game->data->map_height * game->block_size)
	{
		map_x = (int)(xn / (game->block_size));
		map_y = (int)(yn / (game->block_size));
		if (ray_angle > M_PI)
			map_y--;
		if (map_x >= 0 && map_x < game->data->map_width && map_y >= 0 && \
		map_y < game->data->map_height)
		{
			if (game->data->map[map_y][map_x] == '1')
			{
				game->ray.hx = xn;
				game->ray.hy = yn;
				game->ray.dis_h = hypot(game->player->px - xn, \
				game->player->py - yn);
				return ;
			}
			else
			{
				xn += xs;
				yn += ys;
			}
		}
		else
			break ;
	}
	game->ray.dis_h = INFINITY;
}

void	find_vertical(t_cub *game, float ray_angle)
{
	float	xn;
	float	yn;
	float	xs;
	float	ys;
	int		map_x;
	int		map_y;

	if (ray_angle == M_PI_2 || ray_angle == 3 * M_PI_2)
	{
		game->ray.vx = game->player->px;
		game->ray.vy = game->player->py;
		game->ray.dis_v = INFINITY;
		return ;
	}
	if (ray_angle < M_PI_2 || ray_angle > 3 * M_PI_2)
	{
		xn = game->player->px + (game->block_size - \
		fmod(game->player->px, game->block_size));
		xs = game->block_size;
	}
	else
	{
		xn = game->player->px - fmod(game->player->px, game->block_size);
		xs = -(game->block_size);
	}
	ys = xs * tan(ray_angle);
	yn = game->player->py + (xn - game->player->px) * tan(ray_angle);
	while (xn >= 0 && xn < game->data->map_width * game->block_size && \
	yn >= 0 && yn < game->data->map_height * game->block_size)
	{
		map_x = (int)(xn / (game->block_size));
		map_y = (int)(yn / (game->block_size));
		if (ray_angle > M_PI_2 && ray_angle < 3 * M_PI_2)
			map_x--;
		if (map_x >= 0 && map_x < game->data->map_width && map_y >= 0 && \
		map_y < game->data->map_height)
		{
			if (game->data->map[map_y][map_x] == '1')
			{
				game->ray.vx = xn;
				game->ray.vy = yn;
				game->ray.dis_v = hypot(game->player->px - xn, \
				game->player->py - yn);
				return ;
			}
			else
			{
				xn += xs;
				yn += ys;
			}
		}
		else
			break ;
	}
	game->ray.dis_v = INFINITY;
}

void	cast_rays(t_cub *game)
{
	int		num_rays;
	float	angle_step;
	int		i;

	num_rays = WIDTH;
	angle_step = (M_PI / 3) / num_rays;
	game->ray.ra = game->player->p_a - (M_PI / 6);
	i = 0;
	while (i < num_rays)
	{
		if (game->ray.ra < 0)
			game->ray.ra += 2 * M_PI;
		if (game->ray.ra > 2 * M_PI)
			game->ray.ra -= 2 * M_PI;
		find_horizontal(game, game->ray.ra);
		find_vertical(game, game->ray.ra);
		if (game->ray.dis_h < game->ray.dis_v)
		{
			game->ray.rx = game->ray.hx;
			game->ray.ry = game->ray.hy;
			game->ray.dist = game->ray.dis_h;
		}
		else
		{
			game->ray.rx = game->ray.vx;
			game->ray.ry = game->ray.vy;
			game->ray.dist = game->ray.dis_v;
		}
		mlx_draw_line(game, 1);
		// three_d(game, i);
		game->ray.ra += angle_step;
		i++;
	}
}
