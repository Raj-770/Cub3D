/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:28:28 by rpambhar          #+#    #+#             */
/*   Updated: 2024/06/30 14:27:19 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	game_hook(void *param)
{
	t_cub	*game;

	game = param;
	handle_keys(game);
	cast_rays(game);
	game->player->pdx = cos(game->player->p_a);
	game->player->pdy = sin(game->player->p_a);
}

double	fix_ang(double ang)
{
	if (ang > (2 * M_PI))
		ang -= (2 * M_PI);
	if (ang < 0)
		ang += (2 * M_PI);
	return (ang);
}

int	ft_pixel(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}
