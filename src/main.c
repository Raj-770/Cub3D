/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 16:28:03 by rpambhar          #+#    #+#             */
/*   Updated: 2024/05/15 12:42:29 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int	main(int argc, char **argv)
{
	t_map_data	map_data;
	t_cub		game;


	init(&game);
	if (!parser(argc, argv, &map_data))
		return (0);
	game.data = &map_data;
	// game.data->map = 
	display(&game);
	free_map_data(&map_data);
	mlx_loop_hook(game.mlx_ptr, drawPlayer, &game);
	mlx_loop_hook(game.mlx_ptr, ft_hook, &game);
	mlx_loop(game.mlx_ptr);
	return (0);
}

// printf("NO: %s\n", map_data.no_tex);
// printf("SO: %s\n", map_data.so_tex);
// printf("EA: %s\n", map_data.ea_tex);
// printf("WE: %s\n", map_data.we_tex);
// printf("C: %d\n", map_data.c_color);
// printf("F: %d\n", map_data.f_color);
