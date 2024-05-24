/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   three_d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:42:02 by fnikzad           #+#    #+#             */
/*   Updated: 2024/05/24 17:49:35 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_v_line	init_line(double beginx, double beginy, double endx, double endy)
{
	t_v_line	line;

	line.begin_x = beginx;
	line.begin_y = beginy;
	line.end_x = endx;
	line.end_y = endy;
	return (line);
}

int	draw_line(mlx_image_t *image, t_v_line line, int color)
{
	double	deltax;
	double	deltay;
	int		pixels;
	double	pixelx;
	double	pixely;

	deltay = line.end_y - line.begin_y;
	deltax = line.end_x - line.begin_x;
	pixels = sqrt((deltax * deltax) + (deltay * deltay));
	pixelx = line.begin_x;
	pixely = line.begin_y;
	deltax /= pixels;
	deltay /= pixels;
	while (pixels)
	{
		if (pixelx >= 0 && pixelx < WIDTH && pixely >= 0
			&& pixely < HEIGHT)
			mlx_put_pixel(image, pixelx, pixely, color);
		pixelx += deltax;
		pixely += deltay;
		--pixels;
	}
	return (true);
}


// void	draw_mini_map(t_cub *game;)
// {
// 	t_cub	*game;
// 	int		color;
// 	int		x;
// 	int		y;

// 	game = param;
// 	y = -1;
// 	mlx_delete_image(game->mlx_ptr, game->mlx_img);
// 	game->mlx_img = mlx_new_image(game->mlx_ptr, WIDTH, HEIGHT);
// 	mlx_image_to_window(game->mlx_ptr, game->mlx_img, 0, 0);
// 	while (++y < game->data->map_height)
// 	{
// 		x = 0;
// 		while (game->data->map[y][x])
// 		{
// 			if (game->data->map[y][x] == '1')
// 				color = ft_pixel(255, 255, 255, 125);
// 			else if (game->data->map[y][x] == '0')
// 				color = ft_pixel(0, 0, 0, 125);
// 			else
// 			{
// 				x++;
// 				continue ;
// 			}
// 			draw_square(game, x, y, color);
// 			x++;
// 		}
// 	}
// 	draw_player(game);
// 	// mlx_draw_line(game, 0);
// }

void	three_d(t_cub *game, int i)
{
	game->ray.dist = game->ray.dist * cos(game->ray.ra - game->player->p_a);
	float	height = (HEIGHT * game->block_size) / game->ray.dist;
	if (height > HEIGHT)
		height = HEIGHT;
	float lineoff = HEIGHT / 2 - height / 2;
	t_v_line line;
	line = init_line((0) + i, lineoff, (0) + i, height + lineoff);
	draw_line(game->mlx_img, line, ft_pixel(255, 255, 0, 255));
	line = init_line((0) + i, 0, (0) + i, lineoff);
	draw_line(game->mlx_img, line, ft_pixel(0, 255, 0, 255));
	line = init_line((0) + i, height + lineoff, (0) + i, HEIGHT);
	draw_line(game->mlx_img, line, ft_pixel(0, 32, 91, 255));
}