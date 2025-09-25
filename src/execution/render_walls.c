/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vszpiech                                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 23:47:00 by vszpiech          #+#    #+#             */
/*   Updated: 2025/09/25 23:47:00 by vszpiech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

static int	corrected_height(t_game *game, t_ray *ray)
{
	double	corr;
	double	dist_proj_plane;

	corr = ray->distance * cos(ray->angle - game->player_angle);
	if (corr <= 0.0)
		corr = 1.0;
	dist_proj_plane = (SCREEN_WIDTH / 2.0) / tan(FOV_ANGLE / 2.0);
	return ((int)((TILE_SIZE / corr) * dist_proj_plane));
}

static void	wall_bounds(int height, int *top, int *bot)
{
	*top = (SCREEN_HEIGHT / 2) - (height / 2);
	*bot = (SCREEN_HEIGHT / 2) + (height / 2);
	if (*top < 0)
		*top = 0;
	if (*bot >= SCREEN_HEIGHT)
		*bot = SCREEN_HEIGHT - 1;
}

static void	draw_column_params(t_game *game, int x, t_texture *tex, int *p)
{
	double	step;
	double	tex_pos;
	int		y;
	int		tex_y;

	step = (double)tex->height / (double)p[3];
	tex_pos = 0.0;
	y = p[0];
	while (y < p[0] + p[3])
	{
		tex_y = (int)tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= tex->height)
			tex_y = tex->height - 1;
		put_pixel(game, x, y, get_texture_color(tex, p[2], tex_y));
		tex_pos += step;
		y++;
	}
}

void	render_wall_strip(t_game *game, int strip_id)
{
	int			p[4];
	int			height;
	t_texture	*tex;
	t_ray		*ray;

	ray = &game->rays[strip_id];
	height = corrected_height(game, ray);
	wall_bounds(height, &p[0], &p[1]);
	tex = select_wall_texture(game, ray);
	if (!tex || !tex->addr)
		return ;
	p[2] = calculate_texture_x(ray, tex);
	p[3] = p[1] - p[0] + 1;
	draw_column_params(game, strip_id, tex, p);
}

void	render_walls(t_game *game)
{
	int	i;

	i = 0;
	while (i < NUM_RAYS)
	{
		render_wall_strip(game, i);
		i++;
	}
}
