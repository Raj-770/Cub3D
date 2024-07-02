/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 18:41:38 by rpambhar          #+#    #+#             */
/*   Updated: 2024/07/02 19:25:56 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	handle_keys_helper_1(t_cub *game);
static void	handle_keys_helper_2(t_cub *game);
static int	is_within_bounds(t_cub *game, float new_px, float new_py);
static void	exit_mlx(t_cub *game);

void	handle_keys(t_cub *game)
{
	if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_ESCAPE))
		exit_mlx(game);
	if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_LEFT))
	{
		game->player->p_a -= 0.03;
		game->player->p_a = fix_ang(game->player->p_a);
		game->player->pdx = cos(game->player->p_a);
		game->player->pdy = sin(game->player->p_a);
	}
	if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_RIGHT))
	{
		game->player->p_a += 0.03;
		game->player->p_a = fix_ang(game->player->p_a);
		game->player->pdx = cos(game->player->p_a);
		game->player->pdy = sin(game->player->p_a);
	}
	handle_keys_helper_1(game);
	handle_keys_helper_2(game);
}

static void	handle_keys_helper_1(t_cub *game)
{
	float	new_px;
	float	new_py;

	if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_W))
	{
		new_px = game->player->px + game->player->pdx * 3;
		new_py = game->player->py + game->player->pdy * 3;
		if (is_within_bounds(game, new_px, new_py))
		{
			game->player->px += game->player->pdx * 1.5;
			game->player->py += game->player->pdy * 1.5;
		}
	}
	if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_S))
	{
		new_px = game->player->px - game->player->pdx * 3;
		new_py = game->player->py - game->player->pdy * 3;
		if (is_within_bounds(game, new_px, new_py))
		{
			game->player->px -= game->player->pdx * 1.5;
			game->player->py -= game->player->pdy * 1.5;
		}
	}
}

static void	handle_keys_helper_2(t_cub *game)
{
	float	strafe_angle;
	float	new_px;
	float	new_py;

	if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_A))
	{
		strafe_angle = game->player->p_a - M_PI_2;
		new_px = game->player->px + cos(strafe_angle) * 3;
		new_py = game->player->py + sin(strafe_angle) * 3;
		if (is_within_bounds(game, new_px, new_py))
		{
			game->player->px += cos(strafe_angle) * 1.5;
			game->player->py += sin(strafe_angle) * 1.5;
		}
	}
	if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_D))
	{
		strafe_angle = game->player->p_a + M_PI_2;
		if (is_within_bounds(game, game->player->px + cos(strafe_angle) * 3, \
		game->player->py + sin(strafe_angle) * 3))
		{
			game->player->px += cos(strafe_angle) * 1.5;
			game->player->py += sin(strafe_angle) * 1.5;
		}
	}
}

static int	is_within_bounds(t_cub *game, float new_px, float new_py)
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

static void	exit_mlx(t_cub *game)
{
	free_map_data(game->data);
	mlx_delete_image(game->mlx_ptr, game->mlx_img);
	mlx_close_window(game->mlx_ptr);
	mlx_terminate(game->mlx_ptr);
	exit(EXIT_SUCCESS);
}
