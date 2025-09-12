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
	if (keycode == KEY_W || keycode == KEY_UP)
		game->walk_direction = 1;
	else if (keycode == KEY_S || keycode == KEY_DOWN)
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
	else if (keycode == KEY_M)
	{
		game->mouse_look_enabled = !game->mouse_look_enabled;
		/* Reset last reference so we don't jump when re-enabling */
		game->last_mouse_x = -1;
		game->last_mouse_y = -1;
		if (game->mouse_look_enabled)
			mlx_mouse_hide(game->mlx, game->window);
		else
			mlx_mouse_show(game->mlx, game->window);
	}
	
	return (0);
}

int	handle_keyrelease(int keycode, t_game *game)
{
	if (keycode == KEY_W || keycode == KEY_S || keycode == KEY_UP || keycode == KEY_DOWN)
		game->walk_direction = 0;
	else if (keycode == KEY_A || keycode == KEY_D)
		game->side_direction = 0;
	else if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
		game->turn_direction = 0;
	
	return (0);
}

/*
** Mouse motion handler (MotionNotify event)
** Rotates the view based on horizontal mouse delta.
*/
int	handle_mousemove(int x, int y, t_game *game)
{
    int		dx;
    int		dy;
    (void)y; /* y currently unused; keep to avoid unused warning */

	if (!game->mouse_look_enabled)
		return (0);

	/* First event: initialize reference point */
	if (game->last_mouse_x == -1)
	{
		game->last_mouse_x = x;
		game->last_mouse_y = y;
		return (0);
	}

    dx = x - game->last_mouse_x;
    dy = y - game->last_mouse_y;
    if (dx != 0)
    {
        double delta_angle = (double)dx * (game->mouse_sensitivity > 0 ?
                game->mouse_sensitivity : MOUSE_SENSITIVITY);
        game->player_angle = normalize_angle(game->player_angle + delta_angle);

		/* Keep discrete facing dir roughly in sync (optional) */
		if (game->player_angle >= 7 * PI / 4 || game->player_angle < PI / 4)
			game->config->player.dir = CH_E;
		else if (game->player_angle >= PI / 4 && game->player_angle < 3 * PI / 4)
			game->config->player.dir = CH_S;
		else if (game->player_angle >= 3 * PI / 4 && game->player_angle < 5 * PI / 4)
			game->config->player.dir = CH_W;
		else
			game->config->player.dir = CH_N;
	}

    /* Update vertical camera pitch: moving mouse up should look up (walls shift down) */
    if (dy != 0)
    {
        double pitch_delta = -(double)dy * (game->mouse_pitch_sensitivity > 0 ?
                game->mouse_pitch_sensitivity : MOUSE_PITCH_SENSITIVITY);
        game->camera_pitch_pixels += pitch_delta;
        /* Clamp pitch to keep horizon within screen */
        if (game->camera_pitch_pixels > SCREEN_HEIGHT / 2)
            game->camera_pitch_pixels = SCREEN_HEIGHT / 2;
        if (game->camera_pitch_pixels < -SCREEN_HEIGHT / 2)
            game->camera_pitch_pixels = -SCREEN_HEIGHT / 2;
    }

    game->last_mouse_x = x;
    game->last_mouse_y = y;
    return (0);
}
