/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vszpiech                                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 00:00:00 by vszpiech          #+#    #+#             */
/*   Updated: 2025/09/25 00:00:00 by vszpiech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

void	render_crosshair(t_game *game)
{
	int	cx;
	int	cy;
	int	i;
	int	color;

	cx = SCREEN_WIDTH / 2;
	cy = SCREEN_HEIGHT / 2;
	color = create_rgb(255, 255, 255);
	i = -8;
	while (i <= 8)
	{
		put_pixel(game, cx + i, cy, color);
		put_pixel(game, cx, cy + i, color);
		i++;
	}
}

void	render_hud(t_game *game)
{
	char	buf[256];
	int		y;
	int		color;

	color = 0x00FFFFFF;
	y = 20;
	if (!game->show_hud)
		return ;
	snprintf(buf, sizeof(buf), "Pos: %.1f, %.1f", game->player_x,
		game->player_y);
	mlx_string_put(game->mlx, game->window, 20, y, color, buf);
	y += 18;
	snprintf(buf, sizeof(buf), "Angle: %.1f deg", game->player_angle * 180.0
		/ PI);
	mlx_string_put(game->mlx, game->window, 20, y, color, buf);
	y += 18;
	snprintf(buf, sizeof(buf), "Frame: %d", game->frame_count);
	mlx_string_put(game->mlx, game->window, 20, y, color, buf);
}
