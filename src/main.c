/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 16:28:03 by rpambhar          #+#    #+#             */
/*   Updated: 2024/05/15 13:17:25 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	leaks(void)
{
	system("leaks Cub3D");
}

int	main(int argc, char **argv)
{
	t_map_data	map_data;

	atexit(leaks);
	if (!parser(argc, argv, &map_data))
		return (free_map_data(&map_data), 0);
	for (int i = 0; i < map_data.map_size; i++)
		printf("%s\n", map_data.map[i]);
	free_map_data(&map_data);
	return (0);
}


