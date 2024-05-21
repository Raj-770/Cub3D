/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trashh.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:11:32 by fnikzad           #+#    #+#             */
/*   Updated: 2024/05/21 13:11:34 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int fix_ang(int a)
{
	if(a>359)
		a-=360;
	if(a<0)
		a+=360;
	return a;
}

float deg_to_rad(int a)
{
	return (a*( PI/180.0));
}

// float distance(ax,ay,bx,by,ang)
// { 
// 	return cos(deg_to_rad(ang))*(bx-ax)-sin(deg_to_rad(ang))*(by-ay);
// }

void	find_vertical(t_cub *game)
{
	int		ys;
	int		xs;
	float	xn;
	float	yn;

// if (game->ray.ra == M_PI_2 || game->ray.ra == 3 * M_PI_2) {
//         // Special case: ray is perfectly vertical
//         game->ray.vx = game->player->px;
//         game->ray.vy = game->player->py;
//         game->ray.dis_v = INFINITY;  // No valid vertical intersection
//         return;
//     }
	// game->ray.ra = game->player->p_a;
	xs = game->block_size - 1;
	ys = xs / tan(game->ray.ra);
	xn = game->block_size - (game->player->px / game->block_size) * game->block_size;
	yn = xn * tan(game->ray.ra);
	if (game->ray.ra < M_2_PI || game->ray.ra > 3 * M_2_PI)
	{
		xn = game->player->px + (game->block_size - fmod(game->player->px, game->block_size));
		xs = game->block_size;
	}
	else
	{
		xn = game->player->px - fmod(game->player->px, game->block_size);
		xs = -game->block_size;
	}
	ys = xs * tan(game->ray.ra);
	yn = game->player->py + (xn - game->player->px) * tan(game->ray.ra);
	while (xn >= 0 && xn < game->data->map_width * game->block_size &&
			yn >= 0 && yn < game->data->map_height * game->block_size)
	{
		int mapX = (int)(xn / game->block_size);
		int mapY = (int)(yn / game->block_size);
		
		if (mapX >= 0 && mapX < game->data->map_width && mapY >= 0 && mapY < game->data->map_height)
		{
			if (game->data->map[mapY][mapX] == '1')
			{
				game->ray.vx = xn;
				game->ray.vy = yn;
				game->ray.dis_v = hypot(game->player->px - xn, game->player->py - yn);
				game->ray.rx = xn;
				game->ray.ry = yn;
				break;
			}
			else
			{
				xn += xs;
				yn += ys;
				game->ray.rx = xn;
				game->ray.ry = yn;
			}
		}
		else
			break;
	}
	// mlx_draw_line(game, 1);
}


void	find_horizontal(t_cub *game)
{
	int		ys;
	int		xs;
	float	xn;
	float	yn;

//  if (game->ray.ra == 0 || game->ray.ra == M_PI) {
//         // Special case: ray is perfectly horizontal
//         game->ray.hx = game->player->px;
//         game->ray.hy = game->player->py;
//         game->ray.dis_h = INFINITY;  // No valid horizontal intersection
//         return;
//     }
	// game->ray.ra = game->player->p_a;
	ys = game->block_size;
	xs = ys / tan(game->ray.ra);
	yn = game->player->py - (game->player->py / game->block_size) * game->block_size;
	xn = yn / tan(game->ray.ra);
	if (game->ray.ra < M_PI)
	{
		yn = game->player->py + (game->block_size - fmod(game->player->py , game->block_size));
		ys = game->block_size;
		xs = ys / tan(game->ray.ra);
	}

	else
	{
		yn = game->player->py - fmod(game->player->py , game->block_size);
		ys = -game->block_size - 1;
		xs = ys / tan(game->ray.ra);
	}
	xn = game->player->px + (yn - game->player->py) / tan(game->ray.ra);

	while (xn >= 0 && xn < game->data->map_width * game->block_size &&
			yn >= 0 && yn < game->data->map_height * game->block_size)
	{
		int mapX = (int)(xn / game->block_size);
		int mapY = (int)(yn / game->block_size);
		
		if (mapX >= 0 && mapX < game->data->map_width && mapY >= 0 && mapY < game->data->map_height)
		{
			if (game->data->map[mapY][mapX] == '1')
			{
				game->ray.hx = xn;
				game->ray.hy = yn;
				game->ray.dis_h = hypot(game->player->px - xn, game->player->py - yn);
				game->ray.rx = xn;
				game->ray.ry = yn;
				break;
			}
			else
			{
				xn += xs;
				yn += ys;
				game->ray.rx = xn;
				game->ray.ry = yn;
			}
		}
		else
			break;
		// mlx_draw_line(game, 1);
	}
}

// void cast_ray(t_cub *game)
// {
// 	int r = 0;
// 	while (r < 20)
// 	{
// 		find_horizontal(game);
// 		find_vertical(game);

// 		if (game->ray.dis_h < game->ray.dis_v) {
// 			game->ray.rx = game->ray.hx;
// 			game->ray.ry = game->ray.hy;
// 			// game->ray.dist = game->ray.dis_h;
// 		}
// 		else
// 		{
// 			game->ray.rx = game->ray.vx;
// 			game->ray.ry = game->ray.vy;
// 			// game->ray.dist = game->ray.dis_v;
// 		}

// 		mlx_draw_line(game, 1);
// 		r++;
// 	}
// }


void cast_rays(t_cub *game)
{
    int num_rays = 60;
    float angle_step = (M_PI / 3) / num_rays;  // 60 degrees field of view divided by the number of rays

    // Initial ray angle: player angle minus half the field of view
    game->ray.ra = game->player->p_a - (M_PI / 6);

    for (int i = 0; i < num_rays; i++)
    {
        // Normalize the ray angle
		if (game->ray.ra < 0)
			game->ray.ra += 2 * M_PI;
		if (game->ray.ra > 2 * M_PI)
			game->ray.ra -= 2 * M_PI;

        // Find horizontal and vertical intersections
        find_horizontal(game);
        find_vertical(game);

        // Compare distances and choose the closer intersection
        if (game->ray.dis_h < game->ray.dis_v) {
            game->ray.rx = game->ray.hx;
            game->ray.ry = game->ray.hy;
            // game->ray.dist = game->ray.dis_h;
        } else {
            game->ray.rx = game->ray.vx;
            game->ray.ry = game->ray.vy;
            // game->ray.dist = game->ray.dis_v;
        }

        // Draw the ray (assuming mlx_draw_line is your function to draw the ray)
        mlx_draw_line(game, 1);

        // Increment the ray angle for the next ray
        game->ray.ra += angle_step;
    }
}
