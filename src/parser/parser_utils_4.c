/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:55:26 by rpambhar          #+#    #+#             */
/*   Updated: 2024/07/06 14:15:15 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	convert_images(t_map_data *data)
{
	char	*temp;

	temp = data->no_tex;
	if (open(data->no_tex, O_RDONLY) != -1)
		data->no_tex = mlx_load_png(data->no_tex);
	free(temp);
	temp = data->so_tex;
	if (open(data->so_tex, O_RDONLY) != -1)
		data->so_tex = mlx_load_png(data->so_tex);
	free(temp);
	temp = data->ea_tex;
	if (open(data->we_tex, O_RDONLY) != -1)
		data->ea_tex = mlx_load_png(data->ea_tex);
	free(temp);
	temp = data->we_tex;
	if (open(data->we_tex, O_RDONLY) != -1)
		data->we_tex = mlx_load_png(data->we_tex);
	free(temp);
	if (!data->no_tex || !data->so_tex || !data->ea_tex || !data->we_tex)
		return (0);
	return (1);
}
