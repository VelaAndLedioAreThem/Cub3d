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
		game->walk_direction = 1;
	else if (keycode == KEY_S)
		game->walk_direction = -1;
	else if (keycode == KEY_A)
		game->side_direction = -1;
	else if (keycode == KEY_D)
		game->side_direction = 1;
	else if (keycode == KEY_LEFT)
		game->turn_direction = -1;
	else if (keycode == KEY_RIGHT)
		game->turn_direction = 1;
	else if (keycode == KEY_ESC)
		cleanup_and_exit(game);
	
	return (0);
}

int	handle_keyrelease(int keycode, t_game *game)
{
	if (keycode == KEY_W || keycode == KEY_S)
		game->walk_direction = 0;
	else if (keycode == KEY_A || keycode == KEY_D)
		game->side_direction = 0;
	else if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
		game->turn_direction = 0;
	
	return (0);
}