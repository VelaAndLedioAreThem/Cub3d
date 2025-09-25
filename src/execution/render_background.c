/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_background.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vszpiech                                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 23:45:00 by vszpiech          #+#    #+#             */
/*   Updated: 2025/09/25 23:45:00 by vszpiech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

static void	render_ceiling(t_game *game)
{
	int	x;
	int	y;
	int	mid;

	mid = SCREEN_HEIGHT / 2;
	y = 0;
	while (y < mid)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			put_pixel(game, x, y, game->config->ceil.value);
			x++;
		}
		y++;
	}
}

static void	render_floor(t_game *game)
{
	int	x;
	int	y;
	int	mid;

	mid = SCREEN_HEIGHT / 2;
	y = mid;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			put_pixel(game, x, y, game->config->floor.value);
			x++;
		}
		y++;
	}
}

void	render_background(t_game *game)
{
	render_ceiling(game);
	render_floor(game);
}
