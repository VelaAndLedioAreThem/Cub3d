/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vela <vela@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 23:47:00 by vszpiech          #+#    #+#             */
/*   Updated: 2025/09/26 13:06:50 by vela             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

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

static void	draw_column_params(struct s_draw_ctx *ctx)
{
	double	step;
	double	tex_pos;
	int		y;
	int		tex_y;

	step = (double)ctx->tex->height / (double)ctx->line_height;
	tex_pos = ((double)ctx->top - ((double)SCREEN_HEIGHT / 2.0
				- (double)ctx->line_height / 2.0)) * step;
	y = ctx->top;
	while (y <= ctx->bot)
	{
		tex_y = (int)tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= ctx->tex->height)
			tex_y = ctx->tex->height - 1;
		put_pixel(ctx->game, ctx->x, y, get_texture_color(ctx->tex, ctx->tex_x,
				tex_y));
		tex_pos += step;
		y++;
	}
}

void	render_wall_strip(t_game *game, int strip_id)
{
	struct s_draw_ctx	ctx;

	ctx.game = game;
	ctx.line_height = corrected_height(game, &game->rays[strip_id]);
	wall_bounds(ctx.line_height, &ctx.top, &ctx.bot);
	ctx.tex = select_wall_texture(game, &game->rays[strip_id]);
	if (!ctx.tex || !ctx.tex->addr)
		return ;
	ctx.tex_x = calculate_texture_x(&game->rays[strip_id], ctx.tex);
	ctx.x = strip_id;
	draw_column_params(&ctx);
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
