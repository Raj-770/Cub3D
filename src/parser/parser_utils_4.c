/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:55:26 by rpambhar          #+#    #+#             */
/*   Updated: 2024/07/08 13:54:48 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	convert_images(t_map_data *data)
{
	char	*temp;

	temp = data->no_tex;
	if (open(data->no_tex, O_RDONLY) == -1 || open(data->so_tex, O_RDONLY) \
	== -1 || open(data->we_tex, O_RDONLY) == 1 || \
	open(data->we_tex, O_RDONLY) == 1)
		return (put_error("Invalid Image Path", 0));
	data->no_tex = mlx_load_png(data->no_tex);
	temp = data->so_tex;
	data->so_tex = mlx_load_png(data->so_tex);
	temp = data->ea_tex;
	data->ea_tex = mlx_load_png(data->ea_tex);
	temp = data->we_tex;
	data->we_tex = mlx_load_png(data->we_tex);
	free(temp);
	if (!data->no_tex || !data->so_tex || !data->ea_tex || !data->we_tex)
		return (0);
	return (1);
}
