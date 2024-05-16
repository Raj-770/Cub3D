/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:05:52 by fnikzad           #+#    #+#             */
/*   Updated: 2024/05/16 17:59:07 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "math.h"

void	draw_rays(t_cub *game)
{
	int	r;
	game->ray.ra = game->player->p_a;
	float	aTan = -1 / tan(game->ray.ra);
	r = 0;
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
				if (game->data->map[game->ray.my][game->ray.mx] == '1')
				{
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
		r++;
	}
	int ray_color = ft_pixel(0, 255, 255, 255);
	mlx_draw_line(game->mlx_img, game->player->px, game->player->py, game->ray.rx, game->ray.ry, ray_color);
}