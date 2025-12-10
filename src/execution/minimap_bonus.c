/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vszpiech                                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 00:00:00 by vszpiech          #+#    #+#             */
/*   Updated: 2025/12/10 00:00:00 by vszpiech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

#define MM_TILE 8
#define MM_PADDING 10

static void	draw_tile(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;
	int	px;
	int	py;

	j = 0;
	while (j < MM_TILE)
	{
		py = y + j;
		i = 0;
		while (i < MM_TILE)
		{
			px = x + i;
			if (px >= 0 && px < SCREEN_WIDTH && py >= 0 && py < SCREEN_HEIGHT)
				put_pixel(game, px, py, color);
			i++;
		}
		j++;
	}
}

static void	draw_minimap_tiles(t_game *game, int origin_x, int origin_y)
{
	int	mx;
	int	my;

	my = 0;
	while (my < game->config->map.height)
	{
		mx = 0;
		while (mx < game->config->map.width)
		{
			if (game->config->map.grid[my][mx] == CH_WALL)
				draw_tile(game, origin_x + mx * MM_TILE, origin_y + my
					* MM_TILE, create_rgb(120, 120, 120));
			else if (game->config->map.grid[my][mx] == CH_SPACE
				|| game->config->map.grid[my][mx] == CH_VOID
				|| game->config->map.grid[my][mx] == CH_N
				|| game->config->map.grid[my][mx] == CH_S
				|| game->config->map.grid[my][mx] == CH_E
				|| game->config->map.grid[my][mx] == CH_W)
				draw_tile(game, origin_x + mx * MM_TILE, origin_y + my
					* MM_TILE, create_rgb(30, 30, 30));
			mx++;
		}
		my++;
	}
}

static void	draw_direction_line(t_game *game, int x0, int y0)
{
	int	i;
	int	len;
	int	xx;
	int	yy;

	i = 0;
	len = MM_TILE * 2;
	while (i <= len)
	{
		xx = x0 + (int)(cos(game->player_angle) * i);
		yy = y0 + (int)(sin(game->player_angle) * i);
		if (xx >= 0 && xx < SCREEN_WIDTH && yy >= 0 && yy < SCREEN_HEIGHT)
			put_pixel(game, xx, yy, create_rgb(220, 30, 30));
		i++;
	}
}

static void	draw_player_marker(t_game *game, int origin_x, int origin_y)
{
	int	pxx;
	int	pyy;
	int	k;

	pxx = origin_x + (int)((game->player_x / (double)TILE_SIZE) * MM_TILE);
	pyy = origin_y + (int)((game->player_y / (double)TILE_SIZE) * MM_TILE);
	k = 0;
	while (k < 16)
	{
		if (pxx - 2 + (k % 4) >= 0 && pxx - 2 + (k % 4) < SCREEN_WIDTH && pyy
			- 2 + (k / 4) >= 0 && pyy - 2 + (k / 4) < SCREEN_HEIGHT)
			put_pixel(game, pxx - 2 + (k % 4), pyy - 2 + (k / 4),
				create_rgb(220, 30, 30));
		k++;
	}
	draw_direction_line(game, pxx, pyy);
}

void	render_minimap(t_game *game)
{
	int	origin_x;
	int	origin_y;

	if (!game || !game->config || !game->config->map.grid)
		return ;
	origin_x = MM_PADDING;
	origin_y = MM_PADDING;
	draw_minimap_tiles(game, origin_x, origin_y);
	draw_player_marker(game, origin_x, origin_y);
}
