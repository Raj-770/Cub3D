/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:53:56 by fnikzad           #+#    #+#             */
/*   Updated: 2024/05/16 18:21:53 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	draw_square(t_cub *game, int start_x, int start_y, int color)
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
		}
		y++;
	}
}

void	draw_map_2d(void *param)
{
	t_cub	*game;
	int		color;
	int		x;
	int		y;

	game = param;
	y = -1;
	mlx_delete_image(game->mlx_ptr, game->mlx_img);
	game->mlx_img = mlx_new_image(game->mlx_ptr, WIDTH, HEIGHT);
	mlx_image_to_window(game->mlx_ptr, game->mlx_img, 0, 0);
	while (++y < game->data->map_height)
	{
		x = 0;
		while (game->data->map[y][x])
		{
			if (game->data->map[y][x] == '1')
				color = ft_pixel(255, 255, 255, 255);
			else if (game->data->map[y][x] == '0')
				color = ft_pixel(0, 0, 0, 255);
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
	mlx_draw_line(game, 0);
}

void	draw_player(t_cub *game)
{
	int	x;
	int	y;
	int	size;
	int	color;

	color = ft_pixel(0, 255, 0, 255);
	size = 8;
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
