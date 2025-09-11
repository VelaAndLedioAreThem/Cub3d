/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vszpiech < vszpiech@student.42wolfsburg.d  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 10:00:00 by vszpiech          #+#    #+#             */
/*   Updated: 2025/09/11 10:00:00 by vszpiech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

void	init_game(t_game *game, t_config *config)
{
	int	i;
	
	game->config = config;
	game->game_running = 1;
	game->frame_count = 0;
	game->turn_direction = 0;
	game->walk_direction = 0;
	game->side_direction = 0;
	
	for (i = 0; i < NUM_RAYS; i++)
	{
		game->rays[i].angle = 0;
		game->rays[i].distance = 0;
		game->rays[i].wall_hit_x = 0;
		game->rays[i].wall_hit_y = 0;
		game->rays[i].was_hit_vertical = 0;
	}
	
	for (i = 0; i < TEX_COUNT; i++)
	{
		game->textures[i].img = NULL;
		game->textures[i].addr = NULL;
		game->textures[i].width = 0;
		game->textures[i].height = 0;
	}
	
	game->mlx = mlx_init();
	if (!game->mlx)
		return;
	
	game->window = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
	if (!game->window)
		return;
	
	game->img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!game->img)
		return;
	
	game->img_addr = mlx_get_data_addr(game->img, &game->bits_per_pixel,
		&game->line_length, &game->endian);
	
	init_player_from_config(config);

	// Initialize continuous player angle from starting direction
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
		config->floor.value = create_rgb(config->floor.r, config->floor.g, config->floor.b);
	else
		config->floor.value = 0x404040;
		
	if (config->ceil.r != -1)
		config->ceil.value = create_rgb(config->ceil.r, config->ceil.g, config->ceil.b);
	else
		config->ceil.value = 0x808080;
}

void	setup_hooks(t_game *game)
{
	mlx_hook(game->window, 2, 1L<<0, handle_keypress, game);
	mlx_hook(game->window, 3, 1L<<1, handle_keyrelease, game);
	mlx_hook(game->window, 17, 1L<<17, cleanup_and_exit, game);
	mlx_loop_hook(game->mlx, game_loop, game);
}

void	update_game(t_game *game)
{
	update_player(game);
	cast_all_rays(game);
}

void	render_game(t_game *game)
{
	render_background(game);
	render_walls(game);
	mlx_put_image_to_window(game->mlx, game->window, game->img, 0, 0);
}

int	game_loop(void *param)
{
	t_game	*game;
	
	game = (t_game *)param;
	
	if (!game->game_running)
		return (0);
	
	update_game(game);
	render_game(game);
	
	game->frame_count++;
	
	return (0);
}

/**
 * cleanup_and_exit - Cleans up resources and exits program
 * @game: Game structure
 * 
 * This function is called when:
 * - User presses ESC key
 * - User clicks red X on window
 * - An error occurs
 * 
 * It ensures all allocated memory and resources are properly freed.
 * 
 * Return: 0 for successful exit
 */
int	cleanup_and_exit(t_game *game)
{
	// Free game-specific data
	free_game_data(game);
	
	// Destroy MLX image if it exists
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	
	// Destroy window if it exists
	if (game->window)
		mlx_destroy_window(game->mlx, game->window);
	
	// Clean up MLX connection
	if (game->mlx)
	{
		// Note: On some systems, mlx_destroy_display might be needed
		// mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	
	// Exit program successfully
	exit(0);
	return (0);
}
