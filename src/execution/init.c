/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vszpiech <vszpiech@student.42.fr>              +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 10:00:00 by vszpiech          #+#    #+#             */
/*   Updated: 2025/09/11 16:37:16 by vszpiech                               */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"
#include <sys/time.h>

/**
 * init_game_struct - Initialize game structure with default values
 * @game: Game structure to initialize
 *
 * This function sets all game structure fields to safe default values.
 * It should be called before parsing or any other initialization.
 */
static void	init_rays(t_game *game)
{
	int	i;

	i = 0;
	while (i < NUM_RAYS)
	{
		game->rays[i].angle = 0.0;
		game->rays[i].wall_hit_x = 0.0;
		game->rays[i].wall_hit_y = 0.0;
		game->rays[i].distance = 0.0;
		game->rays[i].was_hit_vertical = 0;
		game->rays[i].is_ray_facing_up = 0;
		game->rays[i].is_ray_facing_down = 0;
		game->rays[i].is_ray_facing_left = 0;
		game->rays[i].is_ray_facing_right = 0;
		game->rays[i].hit_content = 0;
		i++;
	}
}

static void	init_textures_arr(t_game *game)
{
	int	i;

	i = 0;
	while (i < TEX_COUNT)
	{
		game->textures[i].img = NULL;
		game->textures[i].addr = NULL;
		game->textures[i].bits_per_pixel = 0;
		game->textures[i].line_length = 0;
		game->textures[i].endian = 0;
		game->textures[i].width = 0;
		game->textures[i].height = 0;
		i++;
	}
}

void	init_game_struct(t_game *game)
{
	ft_memset(game, 0, sizeof(t_game));
	game->mlx = NULL;
	game->window = NULL;
	game->img = NULL;
	game->img_addr = NULL;
	game->config = NULL;
	game->game_running = 0;
	game->frame_count = 0;
	game->turn_direction = 0;
	game->walk_direction = 0;
	game->side_direction = 0;
	init_rays(game);
	init_textures_arr(game);
	game->is_fullscreen = 0;
}

/**
 * error_exit - Prints error message and exits
 * @message: Error message to display
 *
 * This function is used for fatal errors during initialization.
 * It prints "Error\n" followed by the specific error message.
 */
void	error_exit(char *message)
{
	printf("Error\n");
	printf("%s\n", message);
	exit(1);
}

/**
 * create_rgb - Create RGB color value from individual components
 * @r: Red component (0-255)
 * @g: Green component (0-255)
 * @b: Blue component (0-255)
 *
 * Combines RGB components into a single integer suitable for put_pixel().
 * Format: 0x00RRGGBB
 *
 * Return: Combined RGB color value
 */
int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}
