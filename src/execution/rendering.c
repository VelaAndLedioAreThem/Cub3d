/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vszpiech                                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 00:00:00 by vszpiech         #+#    #+#             */
/*   Updated: 2025/09/21 00:00:00 by vszpiech        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

void    render_background(t_game *game)
{
    int x;
    int y;
    int ceiling_height;

    ceiling_height = SCREEN_HEIGHT / 2;
    for (y = 0; y < ceiling_height; y++)
        for (x = 0; x < SCREEN_WIDTH; x++)
            put_pixel(game, x, y, game->config->ceil.value);
    for (; y < SCREEN_HEIGHT; y++)
        for (x = 0; x < SCREEN_WIDTH; x++)
            put_pixel(game, x, y, game->config->floor.value);
}

int     get_texture_color(t_texture *texture, int x, int y)
{
    char *dst;

    if (!texture || !texture->addr)
        return 0;
    if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
        return 0;
    dst = texture->addr + (y * texture->line_length + x * (texture->bits_per_pixel / 8));
    return (*(unsigned int *)dst);
}

static int  calculate_wall_height(double distance)
{
    double dist_proj_plane;

    if (distance <= 0.0)
        distance = 1.0;
    /* Classic projection: h = (tileSize / dist) * dist_to_proj_plane */
    dist_proj_plane = (SCREEN_WIDTH / 2.0) / tan(FOV_ANGLE / 2.0);
    return (int)((TILE_SIZE / distance) * dist_proj_plane);
}

static t_texture *select_wall_texture(t_game *game, t_ray *ray)
{
    if (ray->was_hit_vertical)
        return (ray->is_ray_facing_right) ? &game->textures[TEX_WE]
                                          : &game->textures[TEX_EA];
    else
        return (ray->is_ray_facing_down) ? &game->textures[TEX_NO]
                                         : &game->textures[TEX_SO];
}

static int  calculate_texture_x(t_ray *ray, t_texture *texture)
{
    double offset;

    (void)texture;
    if (ray->was_hit_vertical)
        offset = fmod(ray->wall_hit_y, TILE_SIZE);
    else
        offset = fmod(ray->wall_hit_x, TILE_SIZE);
    if (offset < 0)
        offset += TILE_SIZE;
    return (int)(offset * (double)texture->width / (double)TILE_SIZE);
}

void    render_wall_strip(t_game *game, int strip_id)
{
    t_ray       *ray;
    t_texture   *texture;
    int         wall_height;
    int         wall_top;
    int         wall_bottom;
    int         tex_x;
    int         tex_y;
    int         y;
    double      corrected_distance;

    ray = &game->rays[strip_id];
    corrected_distance = ray->distance * cos(ray->angle - game->player_angle);
    wall_height = calculate_wall_height(corrected_distance);
    wall_top = (SCREEN_HEIGHT / 2) - (wall_height / 2);
    wall_bottom = (SCREEN_HEIGHT / 2) + (wall_height / 2);
    if (wall_top < 0)
        wall_top = 0;
    if (wall_bottom >= SCREEN_HEIGHT)
        wall_bottom = SCREEN_HEIGHT - 1;

    texture = select_wall_texture(game, ray);
    if (!texture || !texture->addr)
        return;
    tex_x = calculate_texture_x(ray, texture);

    for (y = wall_top; y <= wall_bottom; y++)
    {
        tex_y = (y - wall_top) * texture->height / wall_height;
        if (tex_y < 0) tex_y = 0;
        if (tex_y >= texture->height) tex_y = texture->height - 1;
        put_pixel(game, strip_id, y, get_texture_color(texture, tex_x, tex_y));
    }
}

void    render_walls(t_game *game)
{
    int i;

    for (i = 0; i < NUM_RAYS; i++)
        render_wall_strip(game, i);
}
