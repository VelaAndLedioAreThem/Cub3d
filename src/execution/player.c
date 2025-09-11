/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vszpiech < vszpiech@student.42wolfsburg.d  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 10:00:00 by vszpiech          #+#    #+#             */
/*   Updated: 2025/09/11 10:00:00 by vszpiech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

void	init_player_from_config(t_config *config)
{
	config->player.x = (config->player.x * TILE_SIZE) + (TILE_SIZE / 2);
	config->player.y = (config->player.y * TILE_SIZE) + (TILE_SIZE / 2);
}

int	has_wall_collision(t_game *game, double x, double y)
{
	int	map_x, map_y;
	
	if (x < 0 || x >= game->config->map.width * TILE_SIZE || 
		y < 0 || y >= game->config->map.height * TILE_SIZE)
		return (1);
	
	map_x = (int)(x / TILE_SIZE);
	map_y = (int)(y / TILE_SIZE);
	
	return (game->config->map.grid[map_y][map_x] == CH_WALL);
}

void	update_player_position(t_game *game)
{
    double	new_x, new_y;
    double	move_step;
    double	side_step;
    double	angle;

    move_step = game->walk_direction * MOVE_SPEED;
    side_step = game->side_direction * MOVE_SPEED;

    new_x = game->config->player.x;
    new_y = game->config->player.y;

    angle = game->player_angle;

    if (move_step != 0)
    {
        new_x += cos(angle) * move_step;
        new_y += sin(angle) * move_step;
    }

    if (side_step != 0)
    {
        new_x += cos(angle + PI / 2) * side_step;
        new_y += sin(angle + PI / 2) * side_step;
    }

    if (!has_wall_collision(game, new_x, game->config->player.y))
        game->config->player.x = new_x;

    if (!has_wall_collision(game, game->config->player.x, new_y))
        game->config->player.y = new_y;
}

void	update_player_rotation(t_game *game)
{
    double	rotation_step;

    if (game->turn_direction == 0)
        return;

    // Accumulate rotation into a continuous angle
    rotation_step = game->turn_direction * ROTATION_SPEED * (PI / 180);
    game->player_angle = normalize_angle(game->player_angle + rotation_step);

    // Optionally, keep the discrete dir in sync (nearest quadrant)
    if (game->player_angle >= 7 * PI / 4 || game->player_angle < PI / 4)
        game->config->player.dir = CH_E;
    else if (game->player_angle >= PI / 4 && game->player_angle < 3 * PI / 4)
        game->config->player.dir = CH_S;
    else if (game->player_angle >= 3 * PI / 4 && game->player_angle < 5 * PI / 4)
        game->config->player.dir = CH_W;
    else
        game->config->player.dir = CH_N;
}

void	update_player(t_game *game)
{
	update_player_rotation(game);
	update_player_position(game);
}
