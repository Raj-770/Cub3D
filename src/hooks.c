/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:01:47 by rpambhar          #+#    #+#             */
/*   Updated: 2024/05/18 13:24:20 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		ft_hook_helper(t_cub *game);
static double	fix_ang(double ang);

void	ft_hook(void *param)
{
	t_cub	*game;

	game = param;
	// draw_rays(game);
	if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx_ptr);
	game->player->pdx = cos(game->player->p_a);
	game->player->pdy = sin(game->player->p_a);
	ft_hook_helper(game);
}

int is_within_bounds(t_cub *game, float new_px, float new_py)
{
	int grid_x = (int)(new_px / game->block_size);
	int grid_y = (int)(new_py / game->block_size);

	if (grid_x < 0 || grid_x >= game->data->map_width || grid_y < 0 || grid_y >= game->data->map_height)
		return 0;

	if (game->data->map[grid_y][grid_x] == '1')
		return 0;

	return 1;
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
		if(is_within_bounds(game, game->player->px + game->player->pdx * 5, game->player->py + game->player->pdy * 5))
		{
			game->player->px += game->player->pdx * 5;
			game->player->py += game->player->pdy * 5;

		}
	}
	if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_S))
	{
		if(is_within_bounds(game, game->player->px - game->player->pdx * 5, game->player->py - game->player->pdy * 5))
		{
			game->player->px -= game->player->pdx * 5;
			game->player->py -= game->player->pdy * 5;

		}
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
