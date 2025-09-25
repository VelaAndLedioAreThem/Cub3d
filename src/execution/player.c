/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vszpiech                                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 00:00:00 by vszpiech         #+#    #+#             */
/*   Updated: 2025/09/21 00:00:00 by vszpiech        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

/* Currently a no-op. We keep the symbol to match the init flow. */
void	init_player_from_config(t_config *config)
{
    (void)config;
}

static void	move_player(t_game *game)
{
    double move_step;
    double side_step;
    double speed;
    double new_x;
    double new_y;

    speed = MOVE_SPEED;
    if (game->input.shift)
        speed *= 1.8;
    if (game->input.ctrl)
        speed *= 0.5;
    move_step = (double)game->walk_direction * speed;
    side_step = (double)game->side_direction * speed;

    new_x = game->player_x;
    new_y = game->player_y;

    if (move_step != 0.0)
    {
        new_x += cos(game->player_angle) * move_step;
        new_y += sin(game->player_angle) * move_step;
    }
    if (side_step != 0.0)
    {
        new_x += cos(game->player_angle + PI / 2.0) * side_step;
        new_y += sin(game->player_angle + PI / 2.0) * side_step;
    }

    /* slide on walls: resolve X and Y separately */
    if (!has_wall_at(game, new_x, game->player_y))
        game->player_x = new_x;
    if (!has_wall_at(game, game->player_x, new_y))
        game->player_y = new_y;
}

void	update_player(t_game *game)
{
    if (game->turn_direction)
    {
        game->player_angle += (double)game->turn_direction * (ROTATION_SPEED * (PI / 180.0));
        game->player_angle = normalize_angle(game->player_angle);
    }
    move_player(game);
}
