/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:01:47 by rpambhar          #+#    #+#             */
/*   Updated: 2024/06/02 15:20:52 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		ft_hook_helper(t_cub *game);
static double	fix_ang(double ang);

void	ft_hook(void *param)
{
	t_cub	*game;

	game = param;
	cast_rays(game);
	if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx_ptr);
	game->player->pdx = cos(game->player->p_a);
	game->player->pdy = sin(game->player->p_a);
	ft_hook_helper(game);
}

int	is_within_bounds(t_cub *game, float new_px, float new_py)
{
	int	grid_x;
	int	grid_y;

	grid_x = (int)(new_px / game->block_size);
	grid_y = (int)(new_py / game->block_size);
	if (grid_x < 0 || grid_x >= game->data->map_width || \
	grid_y < 0 || grid_y >= game->data->map_height)
		return (0);
	if (game->data->map[grid_y][grid_x] == '1')
		return (0);
	return (1);
}

static void	ft_hook_helper(t_cub *game)
{
	float	strafe_angle;
	float	strafe_dx;
	float	strafe_dy;

	if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_LEFT))
	{
		game->player->p_a -= 0.1;
		game->player->p_a = fix_ang(game->player->p_a);
		game->player->pdx = cos(game->player->p_a);
		game->player->pdy = sin(game->player->p_a);
	}
	if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_RIGHT))
	{
		game->player->p_a += 0.1;
		game->player->p_a = fix_ang(game->player->p_a);
		game->player->pdx = cos(game->player->p_a);
		game->player->pdy = sin(game->player->p_a);
	}
	if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_W))
	{
		if (is_within_bounds(game, game->player->px + game->player->pdx * 3, \
		game->player->py + game->player->pdy * 3))
		{
			game->player->px += game->player->pdx * 3;
			game->player->py += game->player->pdy * 3;
		}
	}
	if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_S))
	{
		if (is_within_bounds(game, game->player->px - game->player->pdx * 3, \
		game->player->py - game->player->pdy * 3))
		{
			game->player->px -= game->player->pdx * 3;
			game->player->py -= game->player->pdy * 3;
		}
	}
	if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_A))
	{
		strafe_angle = game->player->p_a - M_PI_2;
		strafe_dx = cos(strafe_angle) * 3;
		strafe_dy = sin(strafe_angle) * 3;
		if (is_within_bounds(game, game->player->px + strafe_dx, \
		game->player->py + strafe_dy))
		{
			game->player->px += strafe_dx;
			game->player->py += strafe_dy;
		}
	}
	if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_D))
	{
		strafe_angle = game->player->p_a + M_PI_2;
		strafe_dx = cos(strafe_angle) * 3;
		strafe_dy = sin(strafe_angle) * 3;
		if (is_within_bounds(game, game->player->px + strafe_dx, \
		game->player->py + strafe_dy))
		{
			game->player->px += strafe_dx;
			game->player->py += strafe_dy;
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
