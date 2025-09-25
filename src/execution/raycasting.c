/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vszpiech                                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 00:00:00 by vszpiech         #+#    #+#             */
/*   Updated: 2025/09/21 00:00:00 by vszpiech        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

double  normalize_angle(double angle)
{
    while (angle >= TWO_PI)
        angle -= TWO_PI;
    while (angle < 0)
        angle += TWO_PI;
    return angle;
}

double  distance_between_points(double x1, double y1, double x2, double y2)
{
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

static void cast_horizontal(t_game *game, double ray_angle, t_ray *ray)
{
    double x_intercept;
    double y_intercept;
    double x_step;
    double y_step;
    double next_x;
    double next_y;
    int    found = 0;

    ray->is_ray_facing_down = (ray_angle > 0 && ray_angle < PI);
    ray->is_ray_facing_up = !ray->is_ray_facing_down;
    ray->is_ray_facing_right = (ray_angle < PI / 2.0 || ray_angle > 3.0 * PI / 2.0);
    ray->is_ray_facing_left = !ray->is_ray_facing_right;

    /* If ray is perfectly horizontal, it will never hit horizontal grid lines */
    if (fabs(sin(ray_angle)) < 1e-6)
    {
        ray->distance = 1e9;
        ray->is_ray_facing_down = (ray_angle > 0 && ray_angle < PI);
        ray->is_ray_facing_up = !ray->is_ray_facing_down;
        ray->is_ray_facing_right = (ray_angle < PI / 2.0 || ray_angle > 3.0 * PI / 2.0);
        ray->is_ray_facing_left = !ray->is_ray_facing_right;
        return;
    }

    y_intercept = floor(game->player_y / TILE_SIZE) * TILE_SIZE;
    if (ray->is_ray_facing_down)
        y_intercept += TILE_SIZE;
    x_intercept = game->player_x + (y_intercept - game->player_y) / tan(ray_angle);

    y_step = TILE_SIZE * (ray->is_ray_facing_up ? -1 : 1);
    x_step = TILE_SIZE / tan(ray_angle);
    if ((x_step > 0 && ray->is_ray_facing_left) || (x_step < 0 && ray->is_ray_facing_right))
        x_step *= -1;

    next_x = x_intercept;
    next_y = y_intercept + (ray->is_ray_facing_up ? -1 : 0);

    while (next_x >= 0 && next_x < (double)game->config->map.width * TILE_SIZE &&
           next_y >= 0 && next_y < (double)game->config->map.height * TILE_SIZE)
    {
        if (has_wall_at(game, next_x, next_y))
        {
            found = 1;
            ray->wall_hit_x = next_x;
            ray->wall_hit_y = next_y;
            break;
        }
        next_x += x_step;
        next_y += y_step;
    }
    ray->distance = found
        ? distance_between_points(game->player_x, game->player_y, ray->wall_hit_x, ray->wall_hit_y)
        : 1e9;
}

static void cast_vertical(t_game *game, double ray_angle, t_ray *ray)
{
    double x_intercept;
    double y_intercept;
    double x_step;
    double y_step;
    double next_x;
    double next_y;
    int    found = 0;

    ray->is_ray_facing_right = (ray_angle < PI / 2.0 || ray_angle > 3.0 * PI / 2.0);
    ray->is_ray_facing_left = !ray->is_ray_facing_right;
    ray->is_ray_facing_down = (ray_angle > 0 && ray_angle < PI);
    ray->is_ray_facing_up = !ray->is_ray_facing_down;

    /* If ray is perfectly vertical, it will never hit vertical grid lines */
    if (fabs(cos(ray_angle)) < 1e-6)
    {
        ray->distance = 1e9;
        ray->is_ray_facing_right = (ray_angle < PI / 2.0 || ray_angle > 3.0 * PI / 2.0);
        ray->is_ray_facing_left = !ray->is_ray_facing_right;
        ray->is_ray_facing_down = (ray_angle > 0 && ray_angle < PI);
        ray->is_ray_facing_up = !ray->is_ray_facing_down;
        return;
    }

    x_intercept = floor(game->player_x / TILE_SIZE) * TILE_SIZE;
    if (ray->is_ray_facing_right)
        x_intercept += TILE_SIZE;
    y_intercept = game->player_y + (x_intercept - game->player_x) * tan(ray_angle);

    x_step = TILE_SIZE * (ray->is_ray_facing_left ? -1 : 1);
    y_step = TILE_SIZE * tan(ray_angle);
    if ((y_step > 0 && (ray->is_ray_facing_up)) || (y_step < 0 && (ray->is_ray_facing_down)))
        y_step *= -1;

    next_x = x_intercept + (ray->is_ray_facing_left ? -1 : 0);
    next_y = y_intercept;

    while (next_x >= 0 && next_x < (double)game->config->map.width * TILE_SIZE &&
           next_y >= 0 && next_y < (double)game->config->map.height * TILE_SIZE)
    {
        if (has_wall_at(game, next_x, next_y))
        {
            found = 1;
            ray->wall_hit_x = next_x;
            ray->wall_hit_y = next_y;
            break;
        }
        next_x += x_step;
        next_y += y_step;
    }
    ray->distance = found
        ? distance_between_points(game->player_x, game->player_y, ray->wall_hit_x, ray->wall_hit_y)
        : 1e9;
}

void    cast_ray(t_game *game, double ray_angle, int strip_id)
{
    t_ray   h;
    t_ray   v;

    ray_angle = normalize_angle(ray_angle);

    h.angle = ray_angle;
    v.angle = ray_angle;

    cast_horizontal(game, ray_angle, &h);
    cast_vertical(game, ray_angle, &v);

    if (h.distance < v.distance)
    {
        game->rays[strip_id] = h;
        game->rays[strip_id].was_hit_vertical = 0;
    }
    else
    {
        game->rays[strip_id] = v;
        game->rays[strip_id].was_hit_vertical = 1;
    }
    game->rays[strip_id].angle = ray_angle;
}

void    cast_all_rays(t_game *game)
{
    double  ray_angle;
    double  angle_increment;
    int     strip_id;

    /* Sample at the center of each column to reduce edge distortion */
    angle_increment = FOV_ANGLE / (double)NUM_RAYS;
    for (strip_id = 0; strip_id < NUM_RAYS; strip_id++)
    {
        ray_angle = game->player_angle - (FOV_ANGLE / 2.0)
                  + (strip_id + 0.5) * angle_increment;
        cast_ray(game, ray_angle, strip_id);
    }
}
