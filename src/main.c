/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 16:28:03 by rpambhar          #+#    #+#             */
/*   Updated: 2024/05/15 15:11:07 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int	main(int argc, char **argv)
{
	t_map_data	map_data;
	t_cub		game;

	init_map_data(&map_data);
	init(&game);
	if (!parser(argc, argv, &map_data))
		return (0);
	game.data = &map_data;
	display(&game);

	mlx_loop_hook(game.mlx_ptr, drawMap2D, &game);
	mlx_loop_hook(game.mlx_ptr, ft_hook, &game);
	mlx_loop(game.mlx_ptr);
	free_map_data(&map_data);
	return (0);
}
