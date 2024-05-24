/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:57:37 by rpambhar          #+#    #+#             */
/*   Updated: 2024/05/23 18:27:32 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct s_line
{
	int	x0;
	int	y0;
	int	x1;
	int	y1;
	int	color;
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	err2;
	int	eor_x;
	int	eor_y;
}	t_line;

void	initialize_line(t_line *line, t_cub *game, int ray)
{
	line->x0 = game->player->px;
	line->y0 = game->player->py;
	if (!ray)
	{
		line->x1 = game->player->px + 20 * cos(game->player->p_a);
		line->y1 = game->player->py + 20 * sin(game->player->p_a);
	}
	else
	{
		line->x1 = game->ray.rx;
		line->y1 = game->ray.ry;
	}
	line->color = ft_pixel(0, 255, 0, 255);
	line->dx = abs(line->x1 - line->x0);
	line->dy = abs(line->y1 - line->y0);
	if (line->x0 < line->x1)
		line->sx = 1;
	else
		line->sx = -1;
	if (line->y0 < line->y1)
		line->sy = 1;
	else
		line->sy = -1;
	line->err = line->dx - line->dy;
}

void	mlx_draw_line(t_cub *game, int ray)
{
	t_line	line;

	initialize_line(&line, game, ray);
	while (line.x0 != line.x1 || line.y0 != line.y1)
	{
		if (line.y0 >= 0 && line.x0 >= 0 && line.y0 < HEIGHT && line.x0 < WIDTH)
			mlx_put_pixel(game->mlx_img, line.x0, line.y0, line.color);
		line.err2 = 2 * line.err;
		if (line.err2 > -(line.dy))
		{
			line.err -= line.dy;
			line.x0 += line.sx;
		}
		if (line.err2 < line.dx)
		{
			line.err += line.dx;
			line.y0 += line.sy;
		}
	}
}
