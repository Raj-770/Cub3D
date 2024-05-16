/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:01:47 by rpambhar          #+#    #+#             */
/*   Updated: 2024/05/16 18:19:55 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		ft_hook_helper(t_cub *game);
static double	fix_ang(double ang);

void	ft_hook(void *param)
{
	t_cub	*game;

	game = param;
	draw_rays(game);
	if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx_ptr);
	game->player->pdx = cos(game->player->p_a);
	game->player->pdy = sin(game->player->p_a);
	ft_hook_helper(game);
}

static void	ft_hook_helper(t_cub *game)
{
	if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_A))
	{
		game->player->p_a -= 0.1;
		game->player->p_a = fix_ang(game->player->p_a);
		game->player->pdx = cos(game->player->p_a);
		game->player->pdy = sin(game->player->p_a);
	}
	if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_D))
	{
		game->player->p_a += 0.1;
		game->player->p_a = fix_ang(game->player->p_a);
		game->player->pdx = cos(game->player->p_a);
		game->player->pdy = sin(game->player->p_a);
	}
	if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_W))
	{
		game->player->px += game->player->pdx * 5;
		game->player->py += game->player->pdy * 5;
	}
	if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_S))
	{
		game->player->px -= game->player->pdx * 5;
		game->player->py -= game->player->pdy * 5;
	}
}

static double	fix_ang(double ang)
{
	if (ang > (2 * PI))
		ang -= (2 * PI);
	if (ang < 0)
		ang += (2 * PI);
	return (ang);
}
