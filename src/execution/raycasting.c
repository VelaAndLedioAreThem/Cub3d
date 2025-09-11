/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vszpiech < vszpiech@student.42wolfsburg.d  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 10:00:00 by vszpiech          #+#    #+#             */
/*   Updated: 2025/09/11 10:00:00 by vszpiech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

double	normalize_angle(double angle)
{
	while (angle >= TWO_PI)
		angle -= TWO_PI;
	while (angle < 0)
		angle += TWO_PI;
	return (angle);
}

double	distance_between_points(double x1, double y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void	cast_horizontal_ray(t_game *game, double ray_angle, t_ray *ray)
{
	double	x_intercept, y_intercept;
	double	x_step, y_step;
	double	next_x, next_y;
	int		found_wall_hit = 0;
	
	ray->is_ray_facing_down = (ray_angle > 0 && ray_angle < PI);
	ray->is_ray_facing_up = !ray->is_ray_facing_down;
	
	if (ray->is_ray_facing_down)
		y_intercept = floor(game->config->player.y / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
	else
		y_intercept = floor(game->config->player.y / TILE_SIZE) * TILE_SIZE;
	
	x_intercept = game->config->player.x + (y_intercept - game->config->player.y) / tan(ray_angle);
	
	y_step = TILE_SIZE;
	if (ray->is_ray_facing_up)
		y_step *= -1;
	
	x_step = TILE_SIZE / tan(ray_angle);
	if (ray->is_ray_facing_left && x_step > 0)
		x_step *= -1;
	if (ray->is_ray_facing_right && x_step < 0)
		x_step *= -1;
	
	next_x = x_intercept;
	next_y = y_intercept;
	
	if (ray->is_ray_facing_up)
		next_y--;
	
	while (next_x >= 0 && next_x < game->config->map.width * TILE_SIZE &&
		   next_y >= 0 && next_y < game->config->map.height * TILE_SIZE)
	{
		if (has_wall_at(game, next_x, next_y))
		{
			found_wall_hit = 1;
			ray->wall_hit_x = next_x;
			ray->wall_hit_y = next_y;
			break;
		}
		next_x += x_step;
		next_y += y_step;
	}
	
	if (found_wall_hit)
	{
		ray->distance = distance_between_points(game->config->player.x, 
			game->config->player.y, ray->wall_hit_x, ray->wall_hit_y);
	}
	else
	{
		ray->distance = 99999;
	}
}

void	cast_vertical_ray(t_game *game, double ray_angle, t_ray *ray)
{
	double	x_intercept, y_intercept;
	double	x_step, y_step;
	double	next_x, next_y;
	int		found_wall_hit = 0;
	
	ray->is_ray_facing_right = (ray_angle < PI / 2 || ray_angle > 3 * PI / 2);
	ray->is_ray_facing_left = !ray->is_ray_facing_right;
	
	if (ray->is_ray_facing_right)
		x_intercept = floor(game->config->player.x / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
	else
		x_intercept = floor(game->config->player.x / TILE_SIZE) * TILE_SIZE;
	
	y_intercept = game->config->player.y + (x_intercept - game->config->player.x) * tan(ray_angle);
	
	x_step = TILE_SIZE;
	if (ray->is_ray_facing_left)
		x_step *= -1;
	
	y_step = TILE_SIZE * tan(ray_angle);
	if (ray->is_ray_facing_up && y_step > 0)
		y_step *= -1;
	if (ray->is_ray_facing_down && y_step < 0)
		y_step *= -1;
	
	next_x = x_intercept;
	next_y = y_intercept;
	
	if (ray->is_ray_facing_left)
		next_x--;
	
	while (next_x >= 0 && next_x < game->config->map.width * TILE_SIZE &&
		   next_y >= 0 && next_y < game->config->map.height * TILE_SIZE)
	{
		if (has_wall_at(game, next_x, next_y))
		{
			found_wall_hit = 1;
			ray->wall_hit_x = next_x;
			ray->wall_hit_y = next_y;
			break;
		}
		next_x += x_step;
		next_y += y_step;
	}
	
	if (found_wall_hit)
	{
		ray->distance = distance_between_points(game->config->player.x, 
			game->config->player.y, ray->wall_hit_x, ray->wall_hit_y);
	}
	else
	{
		ray->distance = 99999;
	}
}

void	cast_ray(t_game *game, double ray_angle, int strip_id)
{
	t_ray	horizontal_ray, vertical_ray;
	double	horizontal_distance, vertical_distance;
	
	ray_angle = normalize_angle(ray_angle);
	
	horizontal_ray.angle = ray_angle;
	vertical_ray.angle = ray_angle;
	
	cast_horizontal_ray(game, ray_angle, &horizontal_ray);
	horizontal_distance = horizontal_ray.distance;
	
	cast_vertical_ray(game, ray_angle, &vertical_ray);
	vertical_distance = vertical_ray.distance;
	
	if (horizontal_distance < vertical_distance)
	{
		game->rays[strip_id] = horizontal_ray;
		game->rays[strip_id].was_hit_vertical = 0;
	}
	else
	{
		game->rays[strip_id] = vertical_ray;
		game->rays[strip_id].was_hit_vertical = 1;
	}
	
	game->rays[strip_id].angle = ray_angle;
}

void	cast_all_rays(t_game *game)
{
    double	ray_angle;
    double	angle_increment;
    int		strip_id;

    angle_increment = FOV_ANGLE / NUM_RAYS;

    ray_angle = game->player_angle - (FOV_ANGLE / 2);

    for (strip_id = 0; strip_id < NUM_RAYS; strip_id++)
    {
        cast_ray(game, ray_angle, strip_id);
        ray_angle += angle_increment;
    }
}
