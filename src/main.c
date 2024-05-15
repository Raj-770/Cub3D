/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 16:28:03 by rpambhar          #+#    #+#             */
/*   Updated: 2024/05/15 13:26:21 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int	main(int argc, char **argv)
{
	t_map_data	map_data;
	t_cub		game;

	init(&game);
	if (!parser(argc, argv, &map_data))
		return (free_map_data(&map_data), 0);
	game.data = &map_data;
	display(&game);
	for (int i = 0; i < map_data.map_size; i++)
		printf("%s\n", map_data.map[i]);
	free_map_data(&map_data);
	mlx_loop_hook(game.mlx_ptr, drawPlayer, &game);
	mlx_loop_hook(game.mlx_ptr, ft_hook, &game);
	mlx_loop(game.mlx_ptr);
	return (0);
}


