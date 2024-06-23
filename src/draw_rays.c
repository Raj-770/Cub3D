/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:05:52 by fnikzad           #+#    #+#             */
/*   Updated: 2024/06/23 22:03:11 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	cast_rays_helper(t_cub *game);

void	cast_rays(t_cub *game)
{
	int		num_rays;
	float	angle_step;
	int		i;

	num_rays = WIDTH;
	angle_step = (M_PI / 3) / num_rays;
	game->ray.ra = game->player->p_a - (M_PI / 6);
	i = 0;
	while (i < num_rays)
	{
		if (game->ray.ra < 0)
			game->ray.ra += 2 * M_PI;
		if (game->ray.ra > 2 * M_PI)
			game->ray.ra -= 2 * M_PI;
		find_horizontal(game, game->ray.ra);
		find_vertical(game, game->ray.ra);
		cast_rays_helper(game);
		three_d(game, i);
		game->ray.ra += angle_step;
		i++;
	}
}

static void	cast_rays_helper(t_cub *game)
{
	if (game->ray.dis_h < game->ray.dis_v)
	{
		game->ray.rx = game->ray.hx;
		game->ray.ry = game->ray.hy;
		game->ray.dist = game->ray.dis_h;
		game->ray.side_flag = 1;
	}
	else
	{
		game->ray.rx = game->ray.vx;
		game->ray.ry = game->ray.vy;
		game->ray.dist = game->ray.dis_v;
		game->ray.side_flag = 0;
	}
}
