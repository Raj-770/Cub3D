/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:28:28 by rpambhar          #+#    #+#             */
/*   Updated: 2024/06/23 18:05:53 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	fix_ang(double ang);
static int		is_within_bounds(t_cub *game, float new_px, float new_py);
static void		exit_mlx(t_cub *game);
static void		handle_keys(t_cub *game);

void	game_hook(void *param)
{
	t_cub	*game;

	game = param;
	handle_keys(game);
	// draw_map_2d(game);
	// mlx_draw_line(game, 0);
	cast_rays(game);
	game->player->pdx = cos(game->player->p_a);
	game->player->pdy = sin(game->player->p_a);
}

static double	fix_ang(double ang)
{
	if (ang > (2 * PI))
		ang -= (2 * PI);
	if (ang < 0)
		ang += (2 * PI);
	return (ang);
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

static void	handle_keys(t_cub *game)
{
	float	strafe_angle;
	float	strafe_dx;
	float	strafe_dy;

	if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_ESCAPE))
		exit_mlx(game);
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
		if (is_within_bounds(game, game->player->px + game->player->pdx * 7, \
		game->player->py + game->player->pdy * 7))
		{
			game->player->px += game->player->pdx * 3;
			game->player->py += game->player->pdy * 3;
		}
	}
	if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_S))
	{
		if (is_within_bounds(game, game->player->px - game->player->pdx * 7, \
		game->player->py - game->player->pdy * 7))
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
