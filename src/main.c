/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 16:28:03 by rpambhar          #+#    #+#             */
/*   Updated: 2024/05/14 18:39:01 by rpambhar         ###   ########.fr       */
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
		return (0);
	free_map_data(&map_data);
	return (0);
}

// printf("NO: %s\n", map_data.no_tex);
// printf("SO: %s\n", map_data.so_tex);
// printf("EA: %s\n", map_data.ea_tex);
// printf("WE: %s\n", map_data.we_tex);
// printf("C: %d\n", map_data.c_color);
// printf("F: %d\n", map_data.f_color);
