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

#include "../../include/execution.h"

 

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->input.w = 1;
	else if (keycode == KEY_S)
		game->input.s = 1;
	else if (keycode == KEY_A)
		game->input.a = 1;
	else if (keycode == KEY_D)
		game->input.d = 1;
	else if (keycode == KEY_LEFT)
		game->input.left = 1;
	else if (keycode == KEY_RIGHT)
		game->input.right = 1;
	else if (keycode == KEY_SHIFT_L || keycode == KEY_SHIFT_R)
		game->input.shift = 1;
	else if (keycode == KEY_CTRL_L || keycode == KEY_CTRL_R)
		game->input.ctrl = 1;
	else if (keycode == KEY_M)
		game->show_minimap = !game->show_minimap;
	else if (keycode == KEY_C)
		game->show_crosshair = !game->show_crosshair;
	else if (keycode == KEY_H)
		game->show_hud = !game->show_hud;
 
	else if (keycode == KEY_F)
		toggle_fullscreen(game);
	else if (keycode == KEY_ESC)
		cleanup_and_exit(game);

	/* Recompute aggregate directions from per-key state */
	game->walk_direction = (game->input.w ? 1 : 0) + (game->input.s ? -1 : 0);
	if (game->walk_direction > 1) game->walk_direction = 1;
	if (game->walk_direction < -1) game->walk_direction = -1;

	game->side_direction = (game->input.d ? 1 : 0) + (game->input.a ? -1 : 0);
	if (game->side_direction > 1) game->side_direction = 1;
	if (game->side_direction < -1) game->side_direction = -1;

	game->turn_direction = (game->input.right ? 1 : 0) + (game->input.left ? -1 : 0);
	if (game->turn_direction > 1) game->turn_direction = 1;
	if (game->turn_direction < -1) game->turn_direction = -1;

	return (0);
}

int	handle_keyrelease(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->input.w = 0;
	else if (keycode == KEY_S)
		game->input.s = 0;
	else if (keycode == KEY_A)
		game->input.a = 0;
	else if (keycode == KEY_D)
		game->input.d = 0;
	else if (keycode == KEY_LEFT)
		game->input.left = 0;
	else if (keycode == KEY_RIGHT)
		game->input.right = 0;
	else if (keycode == KEY_SHIFT_L || keycode == KEY_SHIFT_R)
		game->input.shift = 0;
	else if (keycode == KEY_CTRL_L || keycode == KEY_CTRL_R)
		game->input.ctrl = 0;

	/* Recompute aggregate directions from per-key state */
	game->walk_direction = (game->input.w ? 1 : 0) + (game->input.s ? -1 : 0);
	if (game->walk_direction > 1) game->walk_direction = 1;
	if (game->walk_direction < -1) game->walk_direction = -1;

	game->side_direction = (game->input.d ? 1 : 0) + (game->input.a ? -1 : 0);
	if (game->side_direction > 1) game->side_direction = 1;
	if (game->side_direction < -1) game->side_direction = -1;

	game->turn_direction = (game->input.right ? 1 : 0) + (game->input.left ? -1 : 0);
	if (game->turn_direction > 1) game->turn_direction = 1;
	if (game->turn_direction < -1) game->turn_direction = -1;

	return (0);
}

 
