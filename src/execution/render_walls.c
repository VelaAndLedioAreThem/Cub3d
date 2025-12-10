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

static void	draw_column_params(t_game *game, int x, t_texture *tex,
                        int top, int bot, int tex_x, int line_height)
{
    double  step;
    double  tex_pos;
    int     y;
    int     tex_y;

    /*
     * Use the unclipped wall height for vertical stepping to avoid texture
     * distortion when the wall is taller than the screen. Start the texture
     * at the correct offset if the top got clipped.
     */
    step = (double)tex->height / (double)line_height;
    tex_pos = ((double)top - ((double)SCREEN_HEIGHT / 2.0 - (double)line_height / 2.0)) * step;
    y = top;
    while (y <= bot)
    {
        tex_y = (int)tex_pos;
        if (tex_y < 0)
            tex_y = 0;
        if (tex_y >= tex->height)
            tex_y = tex->height - 1;
        put_pixel(game, x, y, get_texture_color(tex, tex_x, tex_y));
        tex_pos += step;
        y++;
    }
}

void	render_wall_strip(t_game *game, int strip_id)
{
    int         top;
    int         bot;
    int         height;
    int         tex_x;
    t_texture   *tex;
    t_ray       *ray;

    ray = &game->rays[strip_id];
    height = corrected_height(game, ray);
    wall_bounds(height, &top, &bot);
    tex = select_wall_texture(game, ray);
    if (!tex || !tex->addr)
        return ;
    tex_x = calculate_texture_x(ray, tex);
    draw_column_params(game, strip_id, tex, top, bot, tex_x, height);
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
