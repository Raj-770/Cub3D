/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnikzad <fnikzad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:05:52 by fnikzad           #+#    #+#             */
/*   Updated: 2024/05/21 13:44:06 by fnikzad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void find_horizontal(t_cub *game, float ray_angle)
{
    float xn, yn;
    float xs, ys;

    if (ray_angle == 0 || ray_angle == M_PI) {
        // Special case: ray is perfectly horizontal
        game->ray.hx = game->player->px;
        game->ray.hy = game->player->py;
        game->ray.dis_h = INFINITY;  // No valid horizontal intersection
        return;
    }

    if (ray_angle < M_PI) {  // Ray is facing down
        yn = game->player->py + (game->block_size - fmod(game->player->py, game->block_size));
        ys = game->block_size - 1;
    } else {  // Ray is facing up
        yn = game->player->py - fmod(game->player->py, game->block_size);
        ys = -game->block_size - 1;
    }
    xs = ys / tan(ray_angle);
    xn = game->player->px + (yn - game->player->py) / tan(ray_angle);

    while (xn >= 0 && xn < game->data->map_width * game->block_size &&
           yn >= 0 && yn < game->data->map_height * game->block_size) {
        int mapX = (int)(xn / game->block_size);
        int mapY = (int)(yn / game->block_size);

        if (mapX >= 0 && mapX < game->data->map_width && mapY >= 0 && mapY < game->data->map_height) {
            if (game->data->map[mapY][mapX] == '1') {  // Assuming '1' represents a wall
                game->ray.hx = xn;
                game->ray.hy = yn;
                game->ray.dis_h = hypot(game->player->px - xn, game->player->py - yn);
                return;
            } else {
                xn += xs;
                yn += ys;
            }
        } else {
            break;  // Break if the ray is out of bounds
        }
    }
    game->ray.dis_h = INFINITY;  // No valid horizontal intersection found
}

void find_vertical(t_cub *game, float ray_angle)
{
    float xn, yn;
    float xs, ys;

    if (ray_angle == M_PI_2 || ray_angle == 3 * M_PI_2) {
        // Special case: ray is perfectly vertical
        game->ray.vx = game->player->px;
        game->ray.vy = game->player->py;
        game->ray.dis_v = INFINITY;  // No valid vertical intersection
        return;
    }

    if (ray_angle < M_PI_2 || ray_angle > 3 * M_PI_2) {  // Ray is facing right
        xn = game->player->px + (game->block_size - fmod(game->player->px, game->block_size));
        xs = game->block_size;
    } else {  // Ray is facing left
        xn = game->player->px - fmod(game->player->px, game->block_size);
        xs = -game->block_size;
    }
    ys = xs * tan(ray_angle);
    yn = game->player->py + (xn - game->player->px) * tan(ray_angle);

    while (xn >= 0 && xn < game->data->map_width * game->block_size &&
           yn >= 0 && yn < game->data->map_height * game->block_size) {
        int mapX = (int)(xn / game->block_size);
        int mapY = (int)(yn / game->block_size);

        if (mapX >= 0 && mapX < game->data->map_width && mapY >= 0 && mapY < game->data->map_height) {
            if (game->data->map[mapY][mapX] == '1') {  // Assuming '1' represents a wall
                game->ray.vx = xn;
                game->ray.vy = yn;
                game->ray.dis_v = hypot(game->player->px - xn, game->player->py - yn);
                return;
            } else {
                xn += xs;
                yn += ys;
            }
        } else {
            break;  // Break if the ray is out of bounds
        }
    }
    game->ray.dis_v = INFINITY;  // No valid vertical intersection found
}

void cast_rays(t_cub *game)
{
    int num_rays = 60;
    float angle_step = (M_PI / 3) / num_rays;
    
    game->ray.ra = game->player->p_a - (M_PI / 6);
    
    for (int i = 0; i < num_rays; i++)
    {
        // Normalize the ray angle
        if (game->ray.ra < 0)
            game->ray.ra += 2 * M_PI;
        if (game->ray.ra > 2 * M_PI)
            game->ray.ra -= 2 * M_PI;

        // Find intersections
        find_horizontal(game, game->ray.ra);
        find_vertical(game, game->ray.ra);

        // Compare distances and choose the closer intersection
        if (game->ray.dis_h < game->ray.dis_v)
        {
            game->ray.rx = game->ray.hx;
            game->ray.ry = game->ray.hy;
        }
        else
        {
            game->ray.rx = game->ray.vx;
            game->ray.ry = game->ray.vy;
        }

        // Draw the ray (assuming mlx_draw_line is your function to draw the ray)
        mlx_draw_line(game, 1);

        // Increment the ray angle for the next ray
        game->ray.ra += angle_step;
    }
}
