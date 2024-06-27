/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_horizontal_rays.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 17:56:03 by rpambhar          #+#    #+#             */
/*   Updated: 2024/06/27 13:24:33 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_horizontal_coords(t_cub *game, t_coords *coords);
static int	find_horizontal_ray_height(t_cub *game, t_coords *coords);
static int	find_horizontal_ray_height_helper(t_cub *game, t_coords *coords);

void	find_horizontal(t_cub *game, float ray_angle)
{
	t_coords	coords;

	coords.ray_angle = ray_angle;
	init_horizontal_coords(game, &coords);
	if (!find_horizontal_ray_height(game, &coords))
		return ;
	game->ray.dis_h = INFINITY;
}

static void	init_horizontal_coords(t_cub *game, t_coords *coords)
{
	if (coords->ray_angle == 0 || coords->ray_angle == M_PI)
	{
		game->ray.hx = game->player->px;
		game->ray.hy = game->player->py;
		game->ray.dis_h = INFINITY;
		return ;
	}
	if (coords->ray_angle < M_PI)
	{
		coords->yn = game->player->py + (game->block_size - \
		fmod(game->player->py, game->block_size));
		coords->ys = game->block_size;
	}
	else
	{
		coords->yn = game->player->py - fmod(game->player->py, \
		game->block_size);
		coords->ys = -(game->block_size);
	}
	coords->xs = coords->ys / tan(coords->ray_angle);
	coords->xn = game->player->px + \
	(coords->yn - game->player->py) / tan(coords->ray_angle);
}

static int	find_horizontal_ray_height(t_cub *game, t_coords *coords)
{
	while (coords->xn >= 0 && coords->xn < game->data->map_width * \
	game->block_size && coords->yn >= 0 && \
	coords->yn < game->data->map_height * game->block_size)
	{
		coords->map_x = (int)(coords->xn / (game->block_size));
		coords->map_y = (int)(coords->yn / (game->block_size));
		if (coords->ray_angle > M_PI)
			coords->map_y--;
		if (coords->map_x >= 0 && coords->map_x < game->data->map_width && \
		coords->map_y >= 0 && coords->map_y < game->data->map_height)
		{
			if (!find_horizontal_ray_height_helper(game, coords))
				return (0);
		}
		else
			break ;
	}
	return (1);
}

static int	find_horizontal_ray_height_helper(t_cub *game, t_coords *coords)
{
	if (game->data->map[coords->map_y][coords->map_x] == '1')
	{
		game->ray.hx = coords->xn;
		game->ray.hy = coords->yn;
		game->ray.dis_h = hypot(game->player->px - coords->xn, \
		game->player->py - coords->yn);
		return (0);
	}
	else
	{
		coords->xn += coords->xs;
		coords->yn += coords->ys;
		return (1);
	}
}
