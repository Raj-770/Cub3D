/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:32:46 by fnikzad           #+#    #+#             */
/*   Updated: 2024/05/15 12:58:34 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char map[10][10] = {{"11111111111111111"}, {"10000000000000001"}, {"10100000100000101"}, {"10000000000000001"}, {"10001000100010001"}, {"11111111111111111"}};

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void drawPlayer(void *param)
{
	t_cub	*game;

	game = param;
    int player_size = 8;

    int x, y;
    for (x = game->px; x < game->px + player_size; x++)
    {
        for (y = game->py; y < game->py + player_size; y++)
        {
			uint32_t color = ft_pixel(255, 255, 0, 255);
            mlx_put_pixel(game->mlx_img, x, y, color);
        }
    }
}


void	display(t_cub *game)
{
	game->mlx_img = mlx_new_image(game->mlx_ptr, 1920, 1080);
	mlx_image_to_window(game->mlx_ptr, game->mlx_img, 0, 0);
	mlx_put_string(game->mlx_ptr,"hello", 100, 100);
	drawPlayer(game);
}

void	drawMap2D(t_cub *game)
{
	int color;
	int	x = 0;
	int y = 0;
	int xo;
	int yo;

	while (y < game->mapY)
	{
		x = 0;
		while (x < game->mapX)
		{
			if (map[y * game->mapX + x] == 1)
			{
				color = ft_pixel(255, 255, 255, 255);
			}
			else
				color = ft_pixel(0, 0, 0, 255);
			xo = x * game->mapX;
			yo = y * game->mapY;
			x++;
		}
		y++;
	}

}

void	init(t_cub *game)
{
	game->px = 20;
	game->py = 20;
	game->mapX = 8;
	game->mapY = 8;
	
	game->mlx_ptr = mlx_init(1920, 1080, "mlx42", true);
	
	
}

void ft_hook(void* param)
{
	t_cub *game;

	game = param;
	drawMap2D(game);
	if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx_ptr);
	if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_W))
		game->mlx_img->instances[0].y -= 5;
	if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_S))
		game->mlx_img->instances[0].y += 5;
	if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_A))
		game->mlx_img->instances[0].x -= 5;
	if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_D))
		game->mlx_img->instances[0].x += 5;
}
