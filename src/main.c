/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 16:28:03 by rpambhar          #+#    #+#             */
/*   Updated: 2024/07/08 13:44:43 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_map_data	map_data;
	t_cub		game;

	init_map_data(&map_data);
	if (!parser(argc, argv, &map_data))
	{
		free_map_data(&map_data);
		return (0);
	}
	init_game_data(&game, &map_data);
	mlx_loop_hook(game.mlx_ptr, game_hook, &game);
	mlx_loop(game.mlx_ptr);
	free_map_data(&map_data);
	return (0);
}
