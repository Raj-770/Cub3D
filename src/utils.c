/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:18:46 by rpambhar          #+#    #+#             */
/*   Updated: 2024/05/15 13:18:40 by rpambhar         ###   ########.fr       */
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
		while (data->map[i])
		{
			free(data->map[i]);
			i++;
		}
		free(data->map);
	}
}


