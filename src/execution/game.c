/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vela <vela@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 10:00:00 by vszpiech          #+#    #+#             */
/*   Updated: 2025/09/25 17:58:17 by vela             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

static void	init_flags(t_game *game, t_config *config)
{
	game->config = config;
	game->game_running = 1;
	game->frame_count = 0;
	game->turn_direction = 0;
	game->walk_direction = 0;
	game->side_direction = 0;
	game->show_minimap = 1;
	game->show_crosshair = 1;
	game->show_hud = 1;
	game->mouse_enabled = 1;
	game->mouse_sensitivity = 0.0025;
	game->last_mouse_x = SCREEN_WIDTH / 2;
	game->last_mouse_inited = 0;
}

static int	init_window_and_image(t_game *game)
{
	int	w;
	int	h;

	w = SCREEN_WIDTH;
	h = SCREEN_HEIGHT;
	game->mlx = mlx_init();
	if (!game->mlx)
		return (0);
	game->window = mlx_new_window(game->mlx, w, h, "Cub3D");
	if (!game->window)
		return (0);
	game->img = mlx_new_image(game->mlx, w, h);
	if (!game->img)
		return (0);
	game->img_addr = mlx_get_data_addr(game->img, &game->bits_per_pixel,
			&game->line_length, &game->endian);
	return (1);
}

static void	init_world_and_colors(t_game *game, t_config *config)
{
	init_player_from_config(config);
	game->player_x = (config->player.x + 0.5) * TILE_SIZE;
	game->player_y = (config->player.y + 0.5) * TILE_SIZE;
	if (config->player.dir == CH_N)
		game->player_angle = 3 * PI / 2;
	else if (config->player.dir == CH_S)
		game->player_angle = PI / 2;
	else if (config->player.dir == CH_E)
		game->player_angle = 0;
	else if (config->player.dir == CH_W)
		game->player_angle = PI;
	else
		game->player_angle = 3 * PI / 2;
	load_textures(game);
	if (config->floor.r != -1)
		config->floor.value = create_rgb(config->floor.r, config->floor.g,
				config->floor.b);
	else
		config->floor.value = 0x404040;
	if (config->ceil.r != -1)
		config->ceil.value = create_rgb(config->ceil.r, config->ceil.g,
				config->ceil.b);
	else
		config->ceil.value = 0x808080;
}

static void	init_mouse(t_game *game)
{
	if (!game->mouse_enabled)
		return ;
	mlx_mouse_hide(game->mlx, game->window);
	mlx_mouse_move(game->mlx, game->window, SCREEN_WIDTH / 2, SCREEN_HEIGHT
		/ 2);
	game->last_mouse_x = SCREEN_WIDTH / 2;
	game->last_mouse_inited = 1;
}

void	init_game(t_game *game, t_config *config)
{
	init_game_struct(game);
	init_flags(game, config);
	if (!init_window_and_image(game))
		return ;
	init_world_and_colors(game, config);
	init_mouse(game);
}

/* moved to cleanup.c */
