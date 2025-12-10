/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vszpiech                                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 00:00:00 by vszpiech          #+#    #+#             */
/*   Updated: 2025/12/10 00:00:00 by vszpiech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

static void	recenter_if_edge(int x, t_game *game)
{
	const int	edge = 10;

	if (x < edge || x > (SCREEN_WIDTH - edge))
	{
		mlx_mouse_move(game->mlx, game->window, SCREEN_WIDTH / 2, SCREEN_HEIGHT
			/ 2);
		game->last_mouse_x = SCREEN_WIDTH / 2;
	}
}

void	handle_mouse_look(t_game *game)
{
	int	x;
	int	y;
	int	dx;

	if (!game || !game->mlx || !game->window || !game->mouse_enabled)
		return ;
	if (mlx_mouse_get_pos(game->mlx, game->window, &x, &y) != 0)
	{
		dx = x - (SCREEN_WIDTH / 2);
		if (dx != 0)
		{
			game->player_angle += (double)dx * game->mouse_sensitivity;
			game->player_angle = normalize_angle(game->player_angle);
		}
		mlx_mouse_move(game->mlx, game->window, SCREEN_WIDTH / 2, SCREEN_HEIGHT
			/ 2);
	}
}

int	handle_mousemove(int x, int y, t_game *game)
{
	int	dx;

	(void)y;
	if (!game || !game->mlx || !game->window || !game->mouse_enabled)
		return (0);
	if (!game->last_mouse_inited)
	{
		game->last_mouse_x = x;
		game->last_mouse_inited = 1;
		return (0);
	}
	dx = x - game->last_mouse_x;
	game->last_mouse_x = x;
	if (dx != 0)
	{
		game->player_angle += (double)dx * game->mouse_sensitivity;
		game->player_angle = normalize_angle(game->player_angle);
	}
	recenter_if_edge(x, game);
	return (0);
}
