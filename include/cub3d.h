/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 16:26:50 by rpambhar          #+#    #+#             */
/*   Updated: 2024/05/31 18:37:16 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <math.h>
# include <libft.h>
# include <MLX42.h>
# include <get_next_line.h>

#define	PI 3.1415926535
#define P2	PI/2
#define P3	3 * PI / 2
#define WIDTH 1920
#define HEIGHT 1080
#define DR 0.0174533


typedef struct s_v_line
{
	double	begin_x;
	double	begin_y;
	double	end_x;
	double	end_y;
}	t_v_line;


typedef struct s_ray
{
	int		r;
	int		mx;
	int		my;
	int		mp;
	int		dof;
	float	rx;
	float	ry;
	float	ra;
	float	xo;
	float	yo;
	float	dis_h;
	float	dis_v;
	float	vx;
	float	vy;
	float	hx;
	float	hy;
	float	dist;

}	t_ray;

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
	void	*no_tex;
	void	*ea_tex;
	void	*so_tex;
	void	*we_tex;
	int		c_color;
	int		f_color;
	int		start_px;
	int		start_py;
	int		map_height;
	int		map_width;
	float	player_angle;
}	t_map_data;

typedef struct s_cub
{
	t_player	*player;
	mlx_t		*mlx_ptr;
	t_ray		ray;
	mlx_image_t	*mlx_img;
	t_map_data	*data;
	double		block_size;

	int	size_line;
	int	endian;
	char *img_data;
}	t_cub;

typedef struct s_id
{
	const char	*prefix;
	size_t		length;
	int			count;
}	t_id;

typedef struct s_parser
{
	char	*line;
	char	*trimed_line;
	int		fd;
	int		inside_map;
	int		map_size;
	int		map_capacity;
	t_id	identifiers[6];
}	t_parser;

// Parser
int		parser(int argc, char **argv, t_map_data *data);
int		parse_map_file_line(char *line, t_map_data *data, t_parser *parser);
int		add_line_to_map(char *line, t_map_data *data, t_parser *parser);
int		check_map_rules(t_map_data *data);
void	mlx_draw_line(t_cub *game, int line_length);
void	trim_map(t_map_data *data);
double	degrees_to_radians(double degrees);
int convert_images(t_map_data *data);

// Utils
int		put_error(char *str, int i);
void	free_array(char **array);
void	free_map_data(t_map_data *data);
double	calculate_block_size(int sw, int sh, int mw, int mh);

// Init
void	init_map_data(t_map_data *data);
void	initialize_parser(t_parser *parser);

//init
void	ft_hook(void *param);
void	display(t_cub *game);
void	init(t_cub *game);

void	draw_rays(t_cub *game);
// Hooks
void	ft_hook(void *param);


void	draw_map_2d(void *param);
// void	draw_square(t_cub *game, int start_x, int start_y, int color);
void	draw_square_2(t_cub *game, int start_x, int start_y, int color);
void	draw_player(t_cub *game);
int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);

// void	find_horizontal(t_cub *game);
// void	find_vertical(t_cub *game);
void	cast_rays(t_cub *game);
void	three_d(t_cub *game, int i);
// int	draw_line(t_cub *game, t_v_line line, void *img);
int draw_line(t_cub *game, t_v_line line, mlx_texture_t *tex, float dist);



t_v_line	init_line(double beginx, double beginy, double endx, double endy);




#endif