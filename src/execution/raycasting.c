/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vszpiech                                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 23:40:00 by vszpiech          #+#    #+#             */
/*   Updated: 2025/09/25 23:40:00 by vszpiech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

void	cast_ray(t_game *game, double ray_angle, int strip_id)
{
	t_ray	h;
	t_ray	v;

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

void	cast_all_rays(t_game *game)
{
	double	ray_angle;
	double	inc;
	int		strip_id;

	inc = FOV_ANGLE / (double)NUM_RAYS;
	strip_id = 0;
	while (strip_id < NUM_RAYS)
	{
		ray_angle = game->player_angle - (FOV_ANGLE / 2.0) + ((double)strip_id
				+ 0.5) * inc;
		cast_ray(game, ray_angle, strip_id);
		strip_id++;
	}
}
