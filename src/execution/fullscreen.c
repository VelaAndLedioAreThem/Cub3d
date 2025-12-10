/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fullscreen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vszpiech <vszpiech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 18:00:00 by vszpiech          #+#    #+#             */
/*   Updated: 2025/12/10 21:29:57 by vszpiech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

void	toggle_fullscreen(t_game *game)
{
	if (!game)
		return ;
	game->is_fullscreen = !game->is_fullscreen;
}

void	init_fullscreen(t_game *game)
{
	if (!game)
		return ;
	game->is_fullscreen = 0;
}
