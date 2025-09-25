/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vszpiech                                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 22:45:00 by vszpiech          #+#    #+#             */
/*   Updated: 2025/09/25 22:45:00 by vszpiech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

void	setup_hooks(t_game *game)
{
	mlx_hook(game->window, 2, 1L << 0, handle_keypress, game);
	mlx_hook(game->window, 3, 1L << 1, handle_keyrelease, game);
	mlx_hook(game->window, 6, 1L << 6, handle_mousemove, game);
	mlx_hook(game->window, 17, 1L << 17, cleanup_and_exit, game);
	mlx_loop_hook(game->mlx, game_loop, game);
}
