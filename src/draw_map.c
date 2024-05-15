/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:53:56 by fnikzad           #+#    #+#             */
/*   Updated: 2024/05/15 14:54:46 by fnikzad          ###   ########.fr       */
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


void	drawMap2D(void *param)
{
	t_cub *game = param;
	int color;
	int	player_color;
	int	x = 0;
	int y = 0;

	mlx_delete_image(game->mlx_ptr, game->mlx_img);
	game->mlx_img = mlx_new_image(game->mlx_ptr, 1920, 1080);
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
}