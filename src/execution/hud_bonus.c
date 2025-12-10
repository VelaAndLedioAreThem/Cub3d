/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vszpiech                                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 00:00:00 by vszpiech          #+#    #+#             */
/*   Updated: 2025/12/10 00:00:00 by vszpiech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

static void	put_labeled_int(t_game *game, int *y,
				const char *label, int value)
{
	char	buf[64];
	char	*num;
	int		len;
	int		color;

	color = 0x00FFFFFF;
	num = ft_itoa(value);
	if (!num)
		return ;
	ft_strlcpy(buf, label, sizeof(buf));
	len = ft_strlen(buf);
	if (len < (int) sizeof(buf))
		ft_strlcpy(buf + len, num, sizeof(buf) - (size_t) len);
	free(num);
	mlx_string_put(game->mlx, game->window, 20, *y, color, buf);
	*y += 18;
}

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
	int		y;

	y = 20;
	if (!game->show_hud)
		return ;
	put_labeled_int(game, &y, "PosX: ", (int) game->player_x);
	put_labeled_int(game, &y, "PosY: ", (int) game->player_y);
	put_labeled_int(game, &y, "Angle: ",
		(int)(game->player_angle * 180.0 / PI));
	put_labeled_int(game, &y, "Frame: ", game->frame_count);
}
