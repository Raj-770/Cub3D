/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambhar <rpambhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 16:26:50 by rpambhar          #+#    #+#             */
/*   Updated: 2024/07/08 13:43:42 by rpambhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <math.h>
# include <libft.h>
# include <MLX42.h>
# include <get_next_line.h>

# define WIDTH 1920
# define HEIGHT 1080
# define DR 0.0174533

typedef struct s_v_line
{
	double	begin_x;
	double	begin_y;
	double	end_x;
	double	end_y;
}	t_v_line;

typedef struct s_coords
{
	float	xn;
	float	yn;
	float	xs;
	float	ys;
	int		map_x;
	int		map_y;
	float	ray_angle;
}	t_coords;

typedef struct s_texture
{
	double	deltax;
	double	deltay;
	int		pixels;
	double	pixelx;
	double	pixely;
	double	wall_hit_x;
	double	texture_x;
	double	texture_step;
	double	texture_pos;
	int		texture_y;
	int		texture_pixel_index;
	int		color;
}	t_texture;

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
	int		side_flag;
}	t_ray;

typedef struct s_player
{
	float	px;
	float	py;
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
	int			block_size;
	int			size_line;
	int			endian;
	char		*img_data;
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
int			parser(int argc, char **argv, t_map_data *data);
int			parse_map_file_line(char *line, t_map_data *data, t_parser *parser);
int			add_line_to_map(char *line, t_map_data *data, t_parser *parser);
int			check_map_rules(t_map_data *data);
void		mlx_draw_line(t_cub *game, int line_length);
void		trim_map(t_map_data *data);
double		degrees_to_radians(double degrees);
int			convert_images(t_map_data *data);

// Utils
int			put_error(char *str, int i);
void		free_array(char **array);
void		free_map_data(t_map_data *data);
double		calculate_block_size(int sw, int sh, int mw, int mh);
int			ft_pixel(int r, int g, int b, int a);
double		fix_ang(double ang);

// String array Utils
char		**duplicate_string_array(char **array, int size);
void		free_string_array(char **str);


// Init
void		init_map_data(t_map_data *data);
void		init_game_data(t_cub *game, t_map_data *data);
void		initialize_parser(t_parser *parser);
void		init_tex_data(t_texture *tex_data, t_cub *game, mlx_texture_t *tex, \
t_v_line line);

// Hooks
void		game_hook(void *param);
void		handle_keys(t_cub *game);

// Draw
void		draw_map_2d(t_cub *game);
void		cast_rays(t_cub *game);
void		find_horizontal(t_cub *game, float ray_angle);
void		find_vertical(t_cub *game, float ray_angle);
void		three_d(t_cub *game, int i);
t_v_line	init_line(double beginx, double beginy, double endx, double endy);

#endif