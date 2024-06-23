/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:28:28 by rpambhar          #+#    #+#             */
/*   Updated: 2024/06/23 15:38:25 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	fix_ang(double ang);
static int		is_within_bounds(t_cub *game, float new_px, float new_py);
static void		exit_mlx(t_cub *game);


void	handle_keys(mlx_key_data_t key, void *param)
{
	t_cub	*game;
	float	strafe_angle;
	float	strafe_dx;
	float	strafe_dy;

	game = (t_cub *)param;
	if (key.key == MLX_KEY_ESCAPE)
		exit_mlx(game);
	if (key.key == MLX_KEY_LEFT && (key.action == MLX_PRESS || key.action == MLX_REPEAT))
	{
		game->player->p_a -= 0.1;
		game->player->p_a = fix_ang(game->player->p_a);
		game->player->pdx = cos(game->player->p_a);
		game->player->pdy = sin(game->player->p_a);
	}
	if (key.key == MLX_KEY_RIGHT && (key.action == MLX_PRESS || key.action == MLX_REPEAT))
	{
		game->player->p_a += 0.1;
		game->player->p_a = fix_ang(game->player->p_a);
		game->player->pdx = cos(game->player->p_a);
		game->player->pdy = sin(game->player->p_a);
	}
	if (key.key == MLX_KEY_W && (key.action == MLX_PRESS || key.action == MLX_REPEAT))
	{
		if (is_within_bounds(game, game->player->px + game->player->pdx * 3, \
		game->player->py + game->player->pdy * 3))
		{
			game->player->px += game->player->pdx * 3;
			game->player->py += game->player->pdy * 3;
		}
	}
	if (key.key == MLX_KEY_S && (key.action == MLX_PRESS || key.action == MLX_REPEAT))
	{
		if (is_within_bounds(game, game->player->px - game->player->pdx * 3, \
		game->player->py - game->player->pdy * 3))
		{
			game->player->px -= game->player->pdx * 3;
			game->player->py -= game->player->pdy * 3;
		}
	}
	if (key.key == MLX_KEY_A && (key.action == MLX_PRESS || key.action == MLX_REPEAT))
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
	if (key.key == MLX_KEY_D && (key.action == MLX_PRESS || key.action == MLX_REPEAT))
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