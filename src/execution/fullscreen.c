/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fullscreen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vszpiech                                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 22:45:00 by vszpiech          #+#    #+#             */
/*   Updated: 2025/09/25 22:45:00 by vszpiech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"
#include "../../lib/mlx/mlx_int.h"
#include <X11/Xlib.h>

static void	init_event_base(XEvent *xev, Window win, Atom wm_state)
{
	memset(xev, 0, sizeof(*xev));
	xev->xclient.type = ClientMessage;
	xev->xclient.window = win;
	xev->xclient.message_type = wm_state;
	xev->xclient.format = 32;
}

static void	fill_event_data(XEvent *xev, Atom fs_atom, int enable)
{
	if (enable)
		xev->xclient.data.l[0] = 1;
	else
		xev->xclient.data.l[0] = 0;
	xev->xclient.data.l[1] = fs_atom;
	xev->xclient.data.l[2] = 0;
	xev->xclient.data.l[3] = 1;
}

static void	set_fullscreen_state(t_game *game, int enable)
{
	t_xvar		*xvar;
	t_win_list	*w;
	XEvent		xev;
	Atom		wm_state;
	Atom		fs_atom;

	if (!game || !game->mlx || !game->window)
		return ;
	xvar = (t_xvar *)game->mlx;
	w = (t_win_list *)game->window;
	wm_state = XInternAtom(xvar->display, "_NET_WM_STATE", False);
	fs_atom = XInternAtom(xvar->display, "_NET_WM_STATE_FULLSCREEN", False);
	init_event_base(&xev, w->window, wm_state);
	fill_event_data(&xev, fs_atom, enable);
	XSendEvent(xvar->display, DefaultRootWindow(xvar->display), False,
		SubstructureRedirectMask | SubstructureNotifyMask, &xev);
	XFlush(xvar->display);
}

void	toggle_fullscreen(t_game *game)
{
	static int	is_fullscreen;

	is_fullscreen = !is_fullscreen;
	set_fullscreen_state(game, is_fullscreen);
}
