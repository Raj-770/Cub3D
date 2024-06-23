/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   three_d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:42:02 by fnikzad           #+#    #+#             */
/*   Updated: 2024/06/23 18:37:55 by rpambhar         ###   ########.fr       */
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

int	draw_line_color(mlx_image_t *image, t_v_line line, int color)
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

int	draw_line_3d(t_cub *game, t_v_line line, mlx_texture_t *tex)
{
	(void)tex;
	double deltax = line.end_x - line.begin_x;
	double deltay = line.end_y - line.begin_y;
	int pixels = (int)sqrt((deltax * deltax) + (deltay * deltay));
	double pixelx = line.begin_x;
	double pixely = line.begin_y;
	deltax /= pixels;
	deltay /= pixels;
	while (pixels > 0)
	{
		if (pixelx >= 0 && pixelx < WIDTH && pixely >= 0 && pixely < HEIGHT)
		{
			mlx_put_pixel(game->mlx_img, (int)pixelx, (int)pixely, ft_pixel(255, 0, 0, 255));
		}
		pixelx += deltax;
		pixely += deltay;
		--pixels;
	}
	return true;
}

void	three_d(t_cub *game, int i)
{
	t_v_line	line;
	float		height;
	float		lineoff;
	float		ca;

	ca = game->player->p_a - game->ray.ra;
	if (ca < 0)
		ca += 2 * PI;
	if (ca > 2 * PI)
		ca -= 2 * PI;
	game->ray.dist = game->ray.dist * cos(ca);
	height = (HEIGHT * game->block_size) / game->ray.dist;
	if (height > HEIGHT)
		height = HEIGHT;
	lineoff = HEIGHT / 2 - height / 2;
	line = init_line((0) + i, lineoff, (0) + i, height + lineoff);
	draw_line_3d(game, line, game->data->no_tex);
	line = init_line((0) + i, 0, (0) + i, lineoff);
	draw_line_color(game->mlx_img, line, ft_pixel(0, 255, 0, 255));
	line = init_line((0) + i, height + lineoff, (0) + i, HEIGHT);
	draw_line_color(game->mlx_img, line, ft_pixel(0, 0, 255, 255));
}
