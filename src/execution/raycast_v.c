/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_v.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vszpiech                                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 23:42:30 by vszpiech          #+#    #+#             */
/*   Updated: 2025/09/25 23:42:30 by vszpiech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

static void	v_set_dirs(t_ray *ray, double angle)
{
	ray->is_ray_facing_right = (angle < PI / 2.0 || angle > 3.0 * PI / 2.0);
	ray->is_ray_facing_left = !ray->is_ray_facing_right;
	ray->is_ray_facing_down = (angle > 0 && angle < PI);
	ray->is_ray_facing_up = !ray->is_ray_facing_down;
}

static void	v_init_intercepts(t_game *game, t_ray *ray, double *intercept)
{
	intercept[0] = floor(game->player_x / TILE_SIZE) * TILE_SIZE;
	if (ray->is_ray_facing_right)
		intercept[0] += TILE_SIZE;
	intercept[1] = game->player_y + (intercept[0] - game->player_x)
		* tan(ray->angle);
}

static void	v_calc_steps(t_ray *ray, double *steps)
{
	steps[0] = TILE_SIZE;
	if (ray->is_ray_facing_left)
		steps[0] = -TILE_SIZE;
	steps[1] = TILE_SIZE * tan(ray->angle);
	if ((steps[1] > 0 && ray->is_ray_facing_up) || (steps[1] < 0
			&& ray->is_ray_facing_down))
		steps[1] *= -1;
}

static void	v_scan_from(t_game *game, t_ray *ray, double xi, double yi)
{
	double	steps[2];
	double	nx;
	double	ny;

	v_calc_steps(ray, steps);
	if (ray->is_ray_facing_left)
		nx = xi - 1;
	else
		nx = xi;
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

void	cast_vertical(t_game *game, double ray_angle, t_ray *ray)
{
	double	xi;
	double	yi;
	double	intercept[2];

	v_set_dirs(ray, ray_angle);
	if (fabs(cos(ray_angle)) < 1e-6)
	{
		ray->distance = 1e9;
		return ;
	}
	v_init_intercepts(game, ray, intercept);
	xi = intercept[0];
	yi = intercept[1];
	v_scan_from(game, ray, xi, yi);
}
