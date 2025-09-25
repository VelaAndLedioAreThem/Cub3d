/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codex                                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 00:00:00 by codex             #+#    #+#             */
/*   Updated: 2025/09/25 00:00:00 by codex            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

#define MM_TILE 8
#define MM_PADDING 10

static void draw_rect(t_game *game, int x, int y, int w, int h, int color)
{
    int i, j;

    for (j = 0; j < h; j++)
    {
        int py = y + j;
        if (py < 0 || py >= SCREEN_HEIGHT)
            continue;
        for (i = 0; i < w; i++)
        {
            int px = x + i;
            if (px < 0 || px >= SCREEN_WIDTH)
                continue;
            put_pixel(game, px, py, color);
        }
    }
}

static void draw_line(t_game *game, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0);
    int dy = -abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx + dy;

    while (1)
    {
        if (x0 >= 0 && x0 < SCREEN_WIDTH && y0 >= 0 && y0 < SCREEN_HEIGHT)
            put_pixel(game, x0, y0, color);
        if (x0 == x1 && y0 == y1)
            break;
        int e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
}

void    render_minimap(t_game *game)
{
    int mx, my;
    int color_wall = create_rgb(120, 120, 120);
    int color_floor = create_rgb(30, 30, 30);
    int color_player = create_rgb(220, 30, 30);
    int origin_x = MM_PADDING;
    int origin_y = MM_PADDING;

    if (!game || !game->config || !game->config->map.grid)
        return;

    for (my = 0; my < game->config->map.height; my++)
    {
        for (mx = 0; mx < game->config->map.width; mx++)
        {
            int tile_x = origin_x + mx * MM_TILE;
            int tile_y = origin_y + my * MM_TILE;
            char cell = game->config->map.grid[my][mx];
            if (cell == CH_WALL)
                draw_rect(game, tile_x, tile_y, MM_TILE, MM_TILE, color_wall);
            else if (cell == CH_SPACE || cell == CH_VOID || cell == CH_N || cell == CH_S || cell == CH_E || cell == CH_W)
                draw_rect(game, tile_x, tile_y, MM_TILE, MM_TILE, color_floor);
        }
    }

    /* Player marker */
    {
        double px = game->player_x / (double)TILE_SIZE;
        double py = game->player_y / (double)TILE_SIZE;
        int pxx = origin_x + (int)(px * MM_TILE);
        int pyy = origin_y + (int)(py * MM_TILE);
        draw_rect(game, pxx - 2, pyy - 2, 4, 4, color_player);

        /* Direction line */
        int len = MM_TILE * 2;
        int dx = pxx + (int)(cos(game->player_angle) * len);
        int dy = pyy + (int)(sin(game->player_angle) * len);
        draw_line(game, pxx, pyy, dx, dy, color_player);
    }
}

