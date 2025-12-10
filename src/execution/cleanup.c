/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vszpiech                                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 22:50:00 by vszpiech          #+#    #+#             */
/*   Updated: 2025/09/25 22:50:00 by vszpiech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

int	cleanup_and_exit(t_game *game)
{
	if (game && game->mlx && game->window && game->is_fullscreen)
		toggle_fullscreen(game);
	if (game && game->mlx && game->window)
		mlx_mouse_show(game->mlx, game->window);
	if (game && game->config)
		destroy_configs(game->config);
	free_game_data(game);
	exit(0);
	return (0);
}
