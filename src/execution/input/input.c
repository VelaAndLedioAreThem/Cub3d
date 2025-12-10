/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vszpiech < vszpiech@student.42wolfsburg.d  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 10:00:00 by vszpiech          #+#    #+#             */
/*   Updated: 2025/09/11 10:00:00 by vszpiech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	recompute_walk_side(t_game *game)
{
	game->walk_direction = 0;
	if (game->input.w)
		game->walk_direction += 1;
	if (game->input.s)
		game->walk_direction -= 1;
	if (game->walk_direction > 1)
		game->walk_direction = 1;
	if (game->walk_direction < -1)
		game->walk_direction = -1;
	game->side_direction = 0;
	if (game->input.d)
		game->side_direction += 1;
	if (game->input.a)
		game->side_direction -= 1;
	if (game->side_direction > 1)
		game->side_direction = 1;
	if (game->side_direction < -1)
		game->side_direction = -1;
}

static void	recompute_turn(t_game *game)
{
	game->turn_direction = 0;
	if (game->input.right)
		game->turn_direction += 1;
	if (game->input.left)
		game->turn_direction -= 1;
	if (game->turn_direction > 1)
		game->turn_direction = 1;
	if (game->turn_direction < -1)
		game->turn_direction = -1;
}

/* moved to mouse.c */
int	handle_keypress(int keycode, t_game *game)
{
	apply_keypress(keycode, game);
	recompute_walk_side(game);
	recompute_turn(game);
	return (0);
}

int	handle_keyrelease(int keycode, t_game *game)
{
	apply_keyrelease(keycode, game);
	recompute_walk_side(game);
	recompute_turn(game);
	return (0);
}
