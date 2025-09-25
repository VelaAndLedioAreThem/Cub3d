/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vela <vela@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 23:08:38 by vela              #+#    #+#             */
/*   Updated: 2025/09/25 23:08:40 by vela             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

void	update_game(t_game *game)
{
	update_player(game);
	cast_all_rays(game);
}

void	render_game(t_game *game)
{
	render_background(game);
	render_walls(game);
	if (game->show_minimap)
		render_minimap(game);
	if (game->show_crosshair)
		render_crosshair(game);
	mlx_put_image_to_window(game->mlx, game->window, game->img, 0, 0);
	render_hud(game);
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
