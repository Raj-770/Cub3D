/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   three_d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:42:02 by fnikzad           #+#    #+#             */
/*   Updated: 2024/06/23 23:11:48 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_tex(t_cub *game, mlx_texture_t **tex);
void		init_tex_data(t_texture *tex_data, t_cub *game, \
mlx_texture_t *tex, t_v_line line);

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
	t_texture	tex_data;
	uint8_t		*tex_pixel;

	init_tex_data(&tex_data, game, tex, line);
	while (tex_data.pixels > 0)
	{
		if (tex_data.pixelx >= 0 && tex_data.pixelx < WIDTH && tex_data.pixely \
		>= 0 && tex_data.pixely < HEIGHT)
		{
			tex_data.texture_y = (int)tex_data.texture_pos % tex->height;
			tex_data.texture_pixel_index = tex_data.texture_y * tex->width + \
			(int)tex_data.texture_x % tex->width;
			tex_pixel = &tex->pixels[tex_data.texture_pixel_index * \
			tex->bytes_per_pixel];
			tex_data.color = ft_pixel(tex_pixel[0], tex_pixel[1], \
			tex_pixel[2], tex_pixel[3]);
			mlx_put_pixel(game->mlx_img, (int)tex_data.pixelx, \
			(int)tex_data.pixely, tex_data.color);
		}
		tex_data.pixelx += tex_data.deltax;
		tex_data.pixely += tex_data.deltay;
		tex_data.texture_pos += tex_data.texture_step;
		--tex_data.pixels;
	}
	return (true);
}

void	init_tex_data(t_texture *tex_data, t_cub *game, mlx_texture_t *tex, \
t_v_line line)
{
	tex_data->deltax = line.end_x - line.begin_x;
	tex_data->deltay = line.end_y - line.begin_y;
	tex_data->pixels = (int)sqrt((tex_data->deltax * tex_data->deltax) + \
	(tex_data->deltay * tex_data->deltay));
	tex_data->pixelx = line.begin_x;
	tex_data->pixely = line.begin_y;
	tex_data->deltax /= tex_data->pixels;
	tex_data->deltay /= tex_data->pixels;
	if (game->ray.side_flag == 1)
		tex_data->wall_hit_x = game->ray.rx;
	else
		tex_data->wall_hit_x = game->ray.ry;
	tex_data->texture_x = (tex_data->wall_hit_x - (int)(tex_data->wall_hit_x / \
	game->block_size) * game->block_size) / game->block_size * tex->width;
	tex_data->texture_step = (double)tex->height / (line.end_y - line.begin_y);
	tex_data->texture_pos = 0;
}

void	three_d(t_cub *game, int i)
{
	t_v_line		line;
	float			height;
	float			lineoff;
	float			ca;
	mlx_texture_t	*tex;

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
	set_tex(game, &tex);
	draw_line_3d(game, line, tex);
	line = init_line((0) + i, 0, (0) + i, lineoff);
	draw_line_color(game->mlx_img, line, ft_pixel(0, 255, 0, 255));
	line = init_line((0) + i, height + lineoff, (0) + i, HEIGHT);
	draw_line_color(game->mlx_img, line, ft_pixel(0, 0, 255, 255));
}

static void	set_tex(t_cub *game, mlx_texture_t **tex)
{
	if (game->ray.side_flag == 1)
	{
		if (game->ray.ry < game->player->py)
			*tex = game->data->no_tex;
		else
			*tex = game->data->so_tex;
	}
	else
	{
		if (game->ray.rx < game->player->px)
			*tex = game->data->we_tex;
		else
			*tex = game->data->ea_tex;
	}
}
