/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:53:56 by fnikzad           #+#    #+#             */
/*   Updated: 2024/06/23 18:02:46 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_player(t_cub *game);
static void	draw_square(t_cub *game, int start_x, int start_y, int color);

void	draw_map_2d(t_cub *game)
{
	int		color;
	int		x;
	int		y;

	y = -1;
	while (++y < game->data->map_height)
	{
		x = 0;
		while (game->data->map[y][x])
		{
			if (game->data->map[y][x] == '1')
				color = ft_pixel(255, 255, 255, 125);
			else if (game->data->map[y][x] == '0')
				color = ft_pixel(0, 0, 0, 125);
			else
			{
				x++;
				continue ;
			}
			draw_square(game, x, y, color);
			x++;
		}
	}
	draw_player(game);
}

static void	draw_player(t_cub *game)
{
	int	x;
	int	y;
	int	size;
	int	color;

	color = ft_pixel(0, 255, 0, 255);
	size = 2;
	y = game->player->py;
	while (y < game->player->py + size)
	{
		x = game->player->px;
		while (x < game->player->px + size)
		{
			if (x >= 0 && y >= 0 && y <= 1080)
				mlx_put_pixel(game->mlx_img, x, y, color);
			x++;
		}
		y++;
	}
}

static void	draw_square(t_cub *game, int start_x, int start_y, int color)
{
	int	x;
	int	y;
	int	size;

	size = game->block_size - 1;
	y = start_y * (size + 1);
	while (y < (start_y * (size + 1)) + size)
	{
		x = start_x * (size + 1);
		while (x < (start_x * (size + 1)) + size)
		{
			if (x >= 0 && y >= 0 && y <= 1080)
				mlx_put_pixel(game->mlx_img, x, y, color);
			x++;
			if (x == (start_x * (size + 1)) + size)
				mlx_put_pixel(game->mlx_img, x, y, ft_pixel(0, 0, 0, 0));
		}
		y++;
		if (y == (start_y * (size + 1)) + size)
		{
			x = start_x * (size + 1) - 1;
			while (++x <= (start_x * (size + 1)) + size)
				mlx_put_pixel(game->mlx_img, x, y, ft_pixel(0, 0, 0, 0));
		}
	}
}

int	control_player(t_cub *game)
{
	int	y;
	int	x;

	y = -1;
	while (++y < game->data->map_height)
	{
		x = floor(game->player->px / game->block_size);
		while (game->data->map[y][x])
		{
			if (game->data->map[y][x] == '1')
			{
				if (game->player->px + 8 > (x) * game->block_size)
				{
					return (0);
				}
			}
			x++;
		}
	}
	return (1);
}
