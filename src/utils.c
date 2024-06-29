/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:18:46 by rpambhar          #+#    #+#             */
/*   Updated: 2024/06/29 15:36:21 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	put_error(char *str, int i)
{
	ft_putendl_fd(str, 2);
	return (i);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_map_data(t_map_data *data)
{
	int	i;

	free(data->no_tex);
	free(data->ea_tex);
	free(data->so_tex);
	free(data->we_tex);
	data->c_color = 0;
	data->f_color = 0;
	if (data->map)
	{
		i = 0;
		while (i < data->map_height)
		{
			free(data->map[i]);
			i++;
		}
		free(data->map);
	}
}

double	calculate_block_size(int sw, int sh, int mw, int mh)
{
	double	block_size_width;
	double	block_size_height;
	double	block_size;

	block_size_width = (double)sw / mw;
	block_size_height = (double)sh / mh;
	if (block_size_width < block_size_height)
		block_size = block_size_width;
	else
		block_size = block_size_height;
	return (block_size);
}

double	degrees_to_radians(double degrees)
{
	return (degrees * (M_PI / 180.0));
}
