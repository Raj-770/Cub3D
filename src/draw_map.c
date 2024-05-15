/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:53:56 by fnikzad           #+#    #+#             */
/*   Updated: 2024/05/15 19:21:38 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	draw_square(void *mlx_img, int start_x, int start_y, int size, int color)
{
	int x;
	int y;
	
	y = start_y;
	while (y < start_y + size)
	{
		x = start_x;
		while (x < start_x + size)
		{
			mlx_put_pixel(mlx_img, x, y, color);
			x++;
		}
		y++;
	}
}

void mlx_draw_line(void *mlx_img, int x0, int y0, int x1, int y1, int color)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = x0 < x1 ? 1 : -1;
	int sy = y0 < y1 ? 1 : -1;
	int err = dx - dy;

	while (x0 != x1 || y0 != y1)
	{
		mlx_put_pixel(mlx_img, x0, y0, color);
		int err2 = 2 * err;
		if (err2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (err2 < dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

void	drawMap2D(void *param)
{
	t_cub *game = param;
	int color;
	int	player_color;
	int	x = 0;
	int y = 0;

	mlx_delete_image(game->mlx_ptr, game->mlx_img);
	game->mlx_img = mlx_new_image(game->mlx_ptr, WIDTH, HEIGHT);
	mlx_image_to_window(game->mlx_ptr, game->mlx_img, 0, 0);
	while (y < game->data->map_size)
	{
		x = 0;
		while (game->data->map[y][x])
		{
			if (game->data->map[y][x] == '1')
				color = ft_pixel(255, 255, 255, 255);
			else
				color = ft_pixel(0, 0, 0, 255);
			draw_square(game->mlx_img, x * 65, y * 65, 64, color);
			x++;
		}
		y++;
	}
	player_color = ft_pixel(0, 255, 0, 255);
	draw_square(game->mlx_img, game->player->px, game->player->py, 8, player_color);

	int line_length = 20; // Length of the line segment
	int line_color = ft_pixel(0, 255, 0, 255); // Blue color for the line
	int line_end_x = game->player->px + line_length * cos(game->player->p_a);
	int line_end_y = game->player->py + line_length * sin(game->player->p_a);
	mlx_draw_line(game->mlx_img, game->player->px, game->player->py, line_end_x, line_end_y, line_color);
}