/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 16:26:50 by rpambhar          #+#    #+#             */
/*   Updated: 2024/05/15 14:56:06 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <math.h>
# include <libft.h>
# include <MLX42.h>
# include <get_next_line.h>

#define PI 3.1415926535

typedef struct s_player
{
	int		px;
	int		py;
	float	pdx;
	float	pdy;
	float	p_a;
}	t_player;


typedef struct s_map_data
{
	char	**map;
	char	*no_tex;
	char	*ea_tex;
	char	*so_tex;
	char	*we_tex;
	int		c_color;
	int		f_color;
	int		start_px;
	int		start_py;
	int		map_size;
}	t_map_data;


typedef struct s_cub
{
	t_player	*player;
	mlx_t		*mlx_ptr;
	mlx_image_t	*mlx_img;
	t_map_data	*data;
}	t_cub;

typedef struct s_parser
{
	int		inside_map;
	int		map_size;
	int		map_capacity;
}	t_parser;

// Parser
int		parser(int argc, char **argv, t_map_data *data);
int		parse_map_file_line(char *line, t_map_data *data, t_parser *parser);
int		parse_map_line(char *line, t_map_data *data, t_parser *parser);


// Utils
int		put_error(char *str, int i);
void	free_array(char **array);
void	free_map_data(t_map_data *data);

//init
void	drawPlayer(void *param);
void	ft_hook(void* param);
void	display(t_cub *game);
void	init(t_cub *game);

void	drawMap2D(void *param);
void	draw_square(void *mlx_img, int start_x, int start_y, int size, int color);
int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);




#endif