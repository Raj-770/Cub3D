/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 16:26:50 by rpambhar          #+#    #+#             */
/*   Updated: 2024/05/15 12:38:33 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <math.h>
# include <libft.h>
# include <MLX42.h>
# include <get_next_line.h>


typedef struct s_map_data
{
	char	**map;
	char	*no_tex;
	char	*ea_tex;
	char	*so_tex;
	char	*we_tex;
	int		c_color;
	int		f_color;
}	t_map_data;


typedef struct s_cub
{
	int	px;
	int	py;
	int	mapX;
	int	mapY;

	mlx_t		*mlx_ptr;
	mlx_image_t	*mlx_img;
	t_map_data	*data;
}	t_cub;


// Parser
int		parser(int argc, char **argv, t_map_data *data);
int		parse_map_line(char *line, t_map_data *data);

// Utils
int		put_error(char *str, int i);
void	free_array(char **array);
void	free_map_data(t_map_data *data);

//init
void	drawPlayer(void *param);
void	ft_hook(void* param);
void	display(t_cub *game);
void	init(t_cub *game);



#endif