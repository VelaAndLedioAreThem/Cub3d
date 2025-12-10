/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fullscreen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vszpiech <vszpiech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 22:45:00 by vszpiech          #+#    #+#             */
/*   Updated: 2025/12/09 23:13:22 by vszpiech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

static void	set_fullscreen_state(t_game *game, int enable)
{
	if (!game || !game->mlx || !game->window)
		return ;
	if (mlx_fullscreen(game->mlx, game->window, enable))
		game->is_fullscreen = enable;
}

void	toggle_fullscreen(t_game *game)
{
	if (!game)
		return ;
	set_fullscreen_state(game, !game->is_fullscreen);
}

void	init_fullscreen(t_game *game)
{
	if (!game)
		return ;
	set_fullscreen_state(game, 1);
}
