/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vela <vela@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 10:00:00 by vszpiech          #+#    #+#             */
/*   Updated: 2025/09/25 17:58:17 by vela             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"
#include <X11/Xlib.h>
#include "../../lib/mlx/mlx_int.h"

void	init_game(t_game *game, t_config *config)
{
	int	i;
	
	game->config = config;
	game->game_running = 1;
	game->frame_count = 0;
	game->turn_direction = 0;
	game->walk_direction = 0;
	game->side_direction = 0;
	game->input.w = 0;
	game->input.a = 0;
	game->input.s = 0;
	game->input.d = 0;
	game->input.left = 0;
	game->input.right = 0;
	game->input.shift = 0;
	game->input.ctrl = 0;

	/* Bonus/UI defaults */
	game->show_minimap = 1;
	game->show_crosshair = 1;
	game->show_hud = 1;

	/* Mouse look defaults */
	game->mouse_enabled = 1;
	game->mouse_sensitivity = 0.0025; /* radians per pixel */
	game->last_mouse_x = SCREEN_WIDTH / 2;
	game->last_mouse_inited = 0;
	
	for (i = 0; i < NUM_RAYS; i++)
	{
		game->rays[i].angle = 0;
		game->rays[i].distance = 0;
		game->rays[i].wall_hit_x = 0;
		game->rays[i].wall_hit_y = 0;
		game->rays[i].was_hit_vertical = 0;
	}
	
	for (i = 0; i < TEX_COUNT; i++)
	{
		game->textures[i].img = NULL;
		game->textures[i].addr = NULL;
		game->textures[i].width = 0;
		game->textures[i].height = 0;
	}
	
	game->mlx = mlx_init();
	if (!game->mlx)
		return;
	
	game->window = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
	if (!game->window)
		return;

	/* No fullscreen request: run in windowed mode */
	
	game->img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!game->img)
		return;
	
	game->img_addr = mlx_get_data_addr(game->img, &game->bits_per_pixel,
		&game->line_length, &game->endian);
	
	init_player_from_config(config);

	/* Initialize player world position (pixels) and viewing angle */
	game->player_x = (config->player.x + 0.5) * TILE_SIZE;
	game->player_y = (config->player.y + 0.5) * TILE_SIZE;
	if (config->player.dir == CH_N)
		game->player_angle = 3 * PI / 2;
	else if (config->player.dir == CH_S)
		game->player_angle = PI / 2;
	else if (config->player.dir == CH_E)
		game->player_angle = 0;
	else if (config->player.dir == CH_W)
		game->player_angle = PI;
	else
		game->player_angle = 3 * PI / 2;
	load_textures(game);
	
	if (config->floor.r != -1)
		config->floor.value = create_rgb(config->floor.r, config->floor.g, config->floor.b);
	else
		config->floor.value = 0x404040;
		
	if (config->ceil.r != -1)
		config->ceil.value = create_rgb(config->ceil.r, config->ceil.g, config->ceil.b);
	else
		config->ceil.value = 0x808080;

	/* Prepare mouse look: hide cursor and center it */
	if (game->mouse_enabled)
	{
		mlx_mouse_hide(game->mlx, game->window);
		mlx_mouse_move(game->mlx, game->window, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		game->last_mouse_x = SCREEN_WIDTH / 2;
		game->last_mouse_inited = 1;
	}
}

void	setup_hooks(t_game *game)
{
    mlx_hook(game->window, 2, 1L<<0, handle_keypress, game);
    mlx_hook(game->window, 3, 1L<<1, handle_keyrelease, game);
    /* Mouse motion event */
    mlx_hook(game->window, 6, 1L<<6, handle_mousemove, game);
    mlx_hook(game->window, 17, 1L<<17, cleanup_and_exit, game);
    mlx_loop_hook(game->mlx, game_loop, game);
}

void	update_game(t_game *game)
{
    update_player(game);
    cast_all_rays(game);
}

void	render_game(t_game *game)
{
    render_background(game);
    render_walls(game);
    if (game->show_minimap)
        render_minimap(game);
    if (game->show_crosshair)
        render_crosshair(game);
    mlx_put_image_to_window(game->mlx, game->window, game->img, 0, 0);
    render_hud(game);
}

static void set_fullscreen_state(t_game *game, int enable)
{
    t_xvar  *xvar;
    t_win_list *w;
    XEvent  xev;
    Atom    wm_state, fs_atom;

    if (!game || !game->mlx || !game->window)
        return;
    xvar = (t_xvar*)game->mlx;
    w = (t_win_list*)game->window;
    wm_state = XInternAtom(xvar->display, "_NET_WM_STATE", False);
    fs_atom = XInternAtom(xvar->display, "_NET_WM_STATE_FULLSCREEN", False);
    memset(&xev, 0, sizeof(xev));
    xev.xclient.type = ClientMessage;
    xev.xclient.window = w->window;
    xev.xclient.message_type = wm_state;
    xev.xclient.format = 32;
    xev.xclient.data.l[0] = enable ? 1 : 0; /* _NET_WM_STATE_ADD or REMOVE */
    xev.xclient.data.l[1] = fs_atom;
    xev.xclient.data.l[2] = 0;
    xev.xclient.data.l[3] = 1;
    XSendEvent(xvar->display, DefaultRootWindow(xvar->display), False,
               SubstructureRedirectMask | SubstructureNotifyMask, &xev);
    XFlush(xvar->display);
}

void    toggle_fullscreen(t_game *game)
{
    static int is_fullscreen = 0;
    is_fullscreen = !is_fullscreen;
    set_fullscreen_state(game, is_fullscreen);
}

int	game_loop(void *param)
{
	t_game	*game;
	
	game = (t_game *)param;
	
	if (!game->game_running)
		return (0);
	
	/* Mouse rotation is event-driven; no per-frame query needed */
	update_game(game);
	render_game(game);
	
	game->frame_count++;
	
	return (0);
}

/**
 * cleanup_and_exit - Cleans up resources and exits program
 * @game: Game structure
 * 
 * This function is called when:
 * - User presses ESC key
 * - User clicks red X on window
 * - An error occurs
 * 
 * It ensures all allocated memory and resources are properly freed.
 * 
 * Return: 0 for successful exit
 */
int	cleanup_and_exit(t_game *game)
{
	/* Unified cleanup in one place to avoid double-destroys */
	if (game && game->mlx && game->window)
		mlx_mouse_show(game->mlx, game->window);
	free_game_data(game);
	exit(0);
	return (0);
}
