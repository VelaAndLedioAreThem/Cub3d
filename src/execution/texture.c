/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vszpiech                                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 23:46:00 by vszpiech          #+#    #+#             */
/*   Updated: 2025/09/25 23:46:00 by vszpiech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

int	get_texture_color(t_texture *texture, int x, int y)
{
	char	*dst;

	if (!texture || !texture->addr)
		return (0);
	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0);
	dst = texture->addr + (y * texture->line_length + x
			* (texture->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

static t_tex	wall_tex_vert(t_game *game, t_ray *ray)
{
	if (ray->is_ray_facing_right)
		return (&game->textures[TEX_EA]);
	return (&game->textures[TEX_WE]);
}

static t_tex	wall_tex_horiz(t_game *game, t_ray *ray)
{
	if (ray->is_ray_facing_down)
		return (&game->textures[TEX_SO]);
	return (&game->textures[TEX_NO]);
}

t_tex	select_wall_texture(t_game *game, t_ray *ray)
{
	if (ray->was_hit_vertical)
		return (wall_tex_vert(game, ray));
	return (wall_tex_horiz(game, ray));
}

int	calculate_texture_x(t_ray *ray, t_texture *texture)
{
	double	offset;

	(void)texture;
	if (ray->was_hit_vertical)
		offset = fmod(ray->wall_hit_y, TILE_SIZE);
	else
		offset = fmod(ray->wall_hit_x, TILE_SIZE);
	if (offset < 0)
		offset += TILE_SIZE;
	return ((int)(offset * (double)texture->width / (double)TILE_SIZE));
}
