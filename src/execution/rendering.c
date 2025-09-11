/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vszpiech < vszpiech@student.42wolfsburg.d  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 10:00:00 by vszpiech          #+#    #+#             */
/*   Updated: 2025/09/11 10:00:00 by vszpiech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

/**
 * Rendering functions for the 3D view
 * These functions handle drawing walls and background using raycasting data
 */

void	render_background(t_game *game)
{
	int	x, y;
	int	ceiling_height = SCREEN_HEIGHT / 2;
	
	for (y = 0; y < ceiling_height; y++)
	{
		for (x = 0; x < SCREEN_WIDTH; x++)
		{
			put_pixel(game, x, y, game->config->ceil.value);
		}
	}
	
	for (y = ceiling_height; y < SCREEN_HEIGHT; y++)
	{
		for (x = 0; x < SCREEN_WIDTH; x++)
		{
			put_pixel(game, x, y, game->config->floor.value);
		}
	}
}

int	get_texture_color(t_texture *texture, int x, int y)
{
	char	*dst;
	
	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0x00FF00FF);
	
	dst = texture->addr + (y * texture->line_length + x * (texture->bits_per_pixel / 8));
	return (*(unsigned int*)dst);
}

int	calculate_wall_height(double distance)
{
	if (distance == 0)
		distance = 1;
	
	return ((int)(TILE_SIZE * SCREEN_HEIGHT / distance));
}

t_texture	*select_wall_texture(t_game *game, t_ray *ray)
{
	if (ray->was_hit_vertical)
	{
		if (ray->is_ray_facing_right)
			return (&game->textures[TEX_WE]);
		else
			return (&game->textures[TEX_EA]);
	}
	else
	{
		if (ray->is_ray_facing_down)
			return (&game->textures[TEX_NO]);
		else
			return (&game->textures[TEX_SO]);
	}
}

int	calculate_texture_x(t_ray *ray, t_texture *texture)
{
	double	wall_hit_x, wall_hit_y;
	double	texture_offset_x;
	
	wall_hit_x = ray->wall_hit_x;
	wall_hit_y = ray->wall_hit_y;
	
	if (ray->was_hit_vertical)
		texture_offset_x = fmod(wall_hit_y, TILE_SIZE);
	else
		texture_offset_x = fmod(wall_hit_x, TILE_SIZE);
	
	return ((int)(texture_offset_x * texture->width / TILE_SIZE));
}

void	render_wall_strip(t_game *game, int strip_id)
{
	t_ray		*ray;
	t_texture	*texture;
	int			wall_height;
	int			wall_top_pixel;
	int			wall_bottom_pixel;
	int			texture_x;
	int			texture_y;
	int			y;
	int			color;
	double		distance;
	
	ray = &game->rays[strip_id];
	distance = ray->distance;
	
	// Correct fish-eye using the continuous player angle
	distance = distance * cos(ray->angle - game->player_angle);
	
	wall_height = calculate_wall_height(distance);
	wall_top_pixel = (SCREEN_HEIGHT / 2) - (wall_height / 2);
	wall_bottom_pixel = (SCREEN_HEIGHT / 2) + (wall_height / 2);
	
	if (wall_top_pixel < 0)
		wall_top_pixel = 0;
	if (wall_bottom_pixel >= SCREEN_HEIGHT)
		wall_bottom_pixel = SCREEN_HEIGHT - 1;
	
	texture = select_wall_texture(game, ray);
	texture_x = calculate_texture_x(ray, texture);
	
	if (!texture || !texture->addr)
		return;
	
	for (y = wall_top_pixel; y <= wall_bottom_pixel; y++)
	{
		texture_y = (y - wall_top_pixel) * texture->height / wall_height;
		
		if (texture_y >= texture->height)
			texture_y = texture->height - 1;
		if (texture_y < 0)
			texture_y = 0;
		
		color = get_texture_color(texture, texture_x, texture_y);
		
		if (distance > TILE_SIZE * 5)
		{
			int shade_factor = (int)(distance / (TILE_SIZE * 2));
			if (shade_factor > 3) shade_factor = 3;
			
			int r = ((color >> 16) & 0xFF) / (shade_factor + 1);
			int g = ((color >> 8) & 0xFF) / (shade_factor + 1);
			int b = (color & 0xFF) / (shade_factor + 1);
			color = create_rgb(r, g, b);
		}
		
		put_pixel(game, strip_id, y, color);
	}
}

void	render_walls(t_game *game)
{
	int	strip_id;
	
	for (strip_id = 0; strip_id < NUM_RAYS; strip_id++)
	{
		render_wall_strip(game, strip_id);
	}
}
