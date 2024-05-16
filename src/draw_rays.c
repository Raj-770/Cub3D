/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:05:52 by fnikzad           #+#    #+#             */
/*   Updated: 2024/05/16 20:51:23 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "math.h"
float degToRad(int a)
{
	return a*M_PI/180.0;
}

float distance(ax,ay,bx,by,ang)
{ 
	return cos(degToRad(ang))*(bx-ax)-sin(degToRad(ang))*(by-ay);
}

void	vertical_rays(t_cub *game) 
{
	float	nTan = -tan(game->ray.ra);
	game->ray.dof = 0;
	game->ray.dis_v = 1000000;
	game->ray.vx = game->player->px;
	game->ray.vy = game->player->py;
	if (game->ray.ra > P2 && game->ray.ra < P3)
	{
		game->ray.rx = (((int)game->player->px >> 6)<< 6) - 0.0001;
		game->ray.ry = (game->player->px - game->ray.rx) * nTan + game->player->py;
		game->ray.xo = -game->block_size;
		game->ray.yo = - game->ray.xo * nTan;
	}
	if (game->ray.ra < P2 || game->ray.ra > P3)
	{
		game->ray.rx = (((int)game->player->px >> 6)<< 6) + game->block_size;
		game->ray.ry = (game->player->px - game->ray.rx) * nTan + game->player->py;
		game->ray.xo = game->block_size;
		game->ray.yo = - game->ray.xo * nTan;
	}
	if (game->ray.ra == 0 || game->ray.ra == PI)
	{
		game->ray.rx = game->player->px;
		game->ray.ry = game->player->py;
		game->ray.dof = 8;
	}
	while (game->ray.dof < 8)
	{
		game->ray.mx = (int)(game->ray.rx) >> 6;
		game->ray.my = (int)(game->ray.ry) >> 6;

		if (game->ray.mx >= 0 && game->ray.mx < game->data->map_width &&
			game->ray.my >= 0 && game->ray.my < game->data->map_height)
		{
			if (game->ray.mp > 0 && game->data->map[game->ray.my][game->ray.mx] == '1')
			{
				game->ray.vx = game->ray.rx;
				game->ray.vy = game->ray.ry;
				game->ray.dis_v = distance(game->player->px, game->player->py, game->ray.vx, game->ray.vy, game->ray.ra);
				game->ray.dof = 8;
				// break;
			}
			else
			{
				game->ray.rx += game->ray.xo;
				game->ray.ry += game->ray.yo;
				game->ray.dof += 1;
			}
		}
		else
			break;
	}
}

void	draw_rays(t_cub *game)
{
	int	r;
	game->ray.ra = game->player->p_a;
	float	aTan = -1 / tan(game->ray.ra);
	r = 0;
	game->ray.dis_h = 1000000;
	game->ray.hx = game->player->px;
	game->ray.hy = game->player->py;
	while (r < 1)
	{
		game->ray.dof = 0;
		if (game->ray.ra > PI)
		{
			game->ray.ry = (((int)game->player->py >> 6)<< 6) - 0.0001;
			game->ray.rx = (game->player->py - game->ray.ry) * aTan + game->player->px;
			game->ray.yo = -game->block_size;
			game->ray.xo = - game->ray.yo * aTan;
		}
		if (game->ray.ra < PI)
		{
			game->ray.ry = (((int)game->player->py >> 6)<< 6) + game->block_size;
			game->ray.rx = (game->player->py - game->ray.ry) * aTan + game->player->px;
			game->ray.yo = game->block_size;
			game->ray.xo = - game->ray.yo * aTan;
		}
		if (game->ray.ra == 0 || game->ray.ra == PI)
		{
			game->ray.rx = game->player->px;
			game->ray.ry = game->player->py;
			game->ray.dof = 8;
		}
		while (game->ray.dof < 8)
		{
			game->ray.mx = (int)(game->ray.rx) >> 6;
			game->ray.my = (int)(game->ray.ry) >> 6;

			if (game->ray.mx >= 0 && game->ray.mx < game->data->map_width &&
				game->ray.my >= 0 && game->ray.my < game->data->map_height)
			{
				if (game->ray.mp > 0 && game->data->map[game->ray.my][game->ray.mx] == '1')
				{
					game->ray.hx = game->ray.rx;
					game->ray.hy = game->ray.ry;
					game->ray.dis_h = distance(game->player->px, game->player->py, game->ray.hx, game->ray.hy, game->ray.ra);
					game->ray.dof = 8;
					// break;
				}
				else
				{
					game->ray.rx += game->ray.xo;
					game->ray.ry += game->ray.yo;
					game->ray.dof += 1;
				}
			}
			else
				break;
		}
		vertical_rays(game);
		if (game->ray.dis_v < game->ray.dis_h)
		{
			game->ray.rx = game->ray.vx;
			game->ray.ry = game->ray.vy;
		}
		if (game->ray.dis_v > game->ray.dis_h)
		{
			game->ray.rx = game->ray.hx;
			game->ray.ry = game->ray.hy;
		}
		mlx_draw_line(game, 1);
		r++;
	}
	// int ray_color = ft_pixel(0, 255, 255, 255);
}