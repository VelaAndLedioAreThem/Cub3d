/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vela <vela@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 10:00:00 by vszpiech          #+#    #+#             */
/*   Updated: 2025/09/25 23:00:34 by vela             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

static int	initialize_mouse_if_needed(t_game *game, int x)
{
	if (!game->last_mouse_inited)
	{
		game->last_mouse_x = x;
		game->last_mouse_inited = 1;
		return (1);
	}
	return (0);
}

static void	recenter_mouse_if_edge(t_game *game, int x, int edge)
{
	int	cx;
	int	cy;

	if (!game || !game->mlx || !game->window)
		return ;
	cx = SCREEN_WIDTH / 2;
	cy = SCREEN_HEIGHT / 2;
	if (x < edge || x > (SCREEN_WIDTH - edge))
	{
		mlx_mouse_move(game->mlx, game->window, cx, cy);
		game->last_mouse_x = cx;
		game->last_mouse_inited = 1;
		if (game->dbg_enabled)
			game->dbg_recenters++;
	}
}

int	handle_mousemove(int x, int y, t_game *game)
{
	int			dx;
	const int	edge = 10;

	(void)y;
	if (!game || !game->mlx || !game->window)
		return (0);
	if (!game->mouse_enabled)
		return (0);
	if (initialize_mouse_if_needed(game, x))
		return (0);
	dx = x - game->last_mouse_x;
	game->last_mouse_x = x;
	if (dx != 0)
	{
		game->player_angle += (double)dx * game->mouse_sensitivity;
		game->player_angle = normalize_angle(game->player_angle);
		if (game->dbg_enabled && game->dbg_verbose)
			printf("[DBG] mousemove dx=%d x=%d\n", dx, x);
	}
	if (game->dbg_enabled)
		game->dbg_motion_events++;
	recenter_mouse_if_edge(game, x, edge);
	return (0);
}

int	handle_keypress(int keycode, t_game *game)
{
	set_input_flag(game, keycode, 1);
	if (keycode == KEY_M)
		game->show_minimap = !game->show_minimap;
	else if (keycode == KEY_C)
		game->show_crosshair = !game->show_crosshair;
	else if (keycode == KEY_H)
		game->show_hud = !game->show_hud;
	else if (keycode == KEY_F)
		toggle_fullscreen(game);
	else if (keycode == KEY_ESC)
		cleanup_and_exit(game);
	update_directions(game);
	return (0);
}

int	handle_keyrelease(int keycode, t_game *game)
{
	set_input_flag(game, keycode, 0);
	update_directions(game);
	return (0);
}
