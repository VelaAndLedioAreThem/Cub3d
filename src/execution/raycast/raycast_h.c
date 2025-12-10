/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_h.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vszpiech                                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 23:42:00 by vszpiech          #+#    #+#             */
/*   Updated: 2025/09/25 23:42:00 by vszpiech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	h_set_dirs(t_ray *ray, double angle)
{
	ray->is_ray_facing_down = (angle > 0 && angle < PI);
	ray->is_ray_facing_up = !ray->is_ray_facing_down;
	ray->is_ray_facing_right = (angle < PI / 2.0 || angle > 3.0 * PI / 2.0);
	ray->is_ray_facing_left = !ray->is_ray_facing_right;
}

static void	h_init_intercepts(t_game *game, t_ray *ray, double *intercept)
{
	intercept[1] = floor(game->player_y / TILE_SIZE) * TILE_SIZE;
	if (ray->is_ray_facing_down)
		intercept[1] += TILE_SIZE;
	intercept[0] = game->player_x + (intercept[1] - game->player_y)
		/ tan(ray->angle);
}

static void	h_calc_steps(t_ray *ray, double *steps)
{
	steps[1] = TILE_SIZE;
	if (ray->is_ray_facing_up)
		steps[1] = -TILE_SIZE;
	steps[0] = TILE_SIZE / tan(ray->angle);
	if ((steps[0] > 0 && ray->is_ray_facing_left) || (steps[0] < 0
			&& ray->is_ray_facing_right))
		steps[0] *= -1;
}

static void	h_scan_from(t_game *game, t_ray *ray, double xi, double yi)
{
	double	steps[2];
	double	nx;
	double	ny;

	h_calc_steps(ray, steps);
	nx = xi;
	if (ray->is_ray_facing_up)
		ny = yi - 1;
	else
		ny = yi;
	ray->distance = 1e9;
	while (nx >= 0 && nx < (double)game->config->map.width * TILE_SIZE
		&& ny >= 0 && ny < (double)game->config->map.height * TILE_SIZE)
	{
		if (has_wall_at(game, nx, ny))
		{
			ray->wall_hit_x = nx;
			ray->wall_hit_y = ny;
			ray->distance = distance_between_points(game->player_x,
					game->player_y, nx, ny);
			break ;
		}
		nx += steps[0];
		ny += steps[1];
	}
}

void	cast_horizontal(t_game *game, double ray_angle, t_ray *ray)
{
	double	xi;
	double	yi;
	double	intercept[2];

	h_set_dirs(ray, ray_angle);
	if (fabs(sin(ray_angle)) < 1e-6)
	{
		ray->distance = 1e9;
		return ;
	}
	h_init_intercepts(game, ray, intercept);
	xi = intercept[0];
	yi = intercept[1];
	h_scan_from(game, ray, xi, yi);
}
