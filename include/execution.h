/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vszpiech <vszpiech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 10:00:00 by vszpiech          #+#    #+#             */
/*   Updated: 2025/12/10 13:29:26 by vszpiech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "cub3d.h"
# include <math.h>
# include "mlx.h"

/* ---- Screen and rendering constants ---- */
# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080
# define TILE_SIZE 64

/* ---- Math constants ---- */
# define PI 3.14159265359
# define TWO_PI 6.28318530718
# define FOV_ANGLE 1.04719755

/* ---- Ray configuration ---- */
# define NUM_RAYS SCREEN_WIDTH
# define WALL_STRIP_WIDTH 1

/* ---- Movement constants ---- */
# define MOVE_SPEED 3.0
# define ROTATION_SPEED 3.0

/* ---- Key codes ---- */
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_UP 65362
# define KEY_DOWN 65364
/* reserve key codes if needed */
/* Bonus keys */
# define KEY_SHIFT_L 65505
# define KEY_SHIFT_R 65506
# define KEY_CTRL_L 65507
# define KEY_CTRL_R 65508
# define KEY_M 109
# define KEY_C 99
# define KEY_H 104
# define KEY_F 102

/* ---- Ray structure ---- */
typedef struct s_ray
{
	double	angle;
	double	wall_hit_x;
	double	wall_hit_y;
	double	distance;
	int		was_hit_vertical;
	int		is_ray_facing_up;
	int		is_ray_facing_down;
	int		is_ray_facing_left;
	int		is_ray_facing_right;
	int		hit_content;
}	t_ray;

/* ---- Texture structure ---- */
typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_texture;

typedef t_texture	*t_tex;

/* ---- Game execution structure ---- */
typedef struct s_game
{
	void		*mlx;
	void		*window;
	void		*img;
	char		*img_addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	t_config	*config;
	t_ray		rays[NUM_RAYS];
	t_texture	textures[TEX_COUNT];
	int			game_running;
	int			frame_count;

	int			turn_direction;
	int			walk_direction;
	int			side_direction;

	struct s_input
	{
		int		w;
		int		a;
		int		s;
		int		d;
		int		left;
		int		right;
		int		shift;
		int		ctrl;
	}			input;
	double		player_x;
	double		player_y;
	double		player_angle;

	/* Bonus/UI state */
	int			show_minimap;
	int			show_crosshair;
	int			show_hud;
	int			is_fullscreen;

	/* Mouse look state */
	int			mouse_enabled;
	double		mouse_sensitivity;
	int			last_mouse_x;
	int			last_mouse_inited;
}	t_game;

/* ---- Internal rendering context (wall column) ---- */
struct s_draw_ctx
{
	t_game		*game;
	t_texture	*tex;
	int			x;
	int			top;
	int			bot;
	int			tex_x;
	int			line_height;
};

/* ---- Main execution functions ---- */
int			game_loop(void *param);
void		update_game(t_game *game);
void		render_game(t_game *game);
void		init_game(t_game *game, t_config *config);
void		setup_hooks(t_game *game);

/* ---- Player functions ---- */
void		init_player_from_config(t_config *config);
void		update_player(t_game *game);

/* ---- Raycasting functions ---- */
void		cast_all_rays(t_game *game);
void		cast_ray(t_game *game, double ray_angle, int strip_id);
double		normalize_angle(double angle);
double		distance_between_points(double x1, double y1, double x2, double y2);
void		cast_horizontal(t_game *game, double ray_angle, t_ray *ray);
void		cast_vertical(t_game *game, double ray_angle, t_ray *ray);

/* ---- Rendering functions ---- */
void		render_background(t_game *game);
void		render_walls(t_game *game);
void		render_wall_strip(t_game *game, int strip_id);
void		render_minimap(t_game *game);
void		render_crosshair(t_game *game);
void		render_hud(t_game *game);

/* ---- Texture functions ---- */
void		load_textures(t_game *game);
int			get_texture_color(t_texture *texture, int x, int y);
t_tex		select_wall_texture(t_game *game, t_ray *ray);
int			calculate_texture_x(t_ray *ray, t_texture *texture);

/* ---- Utility functions ---- */
int			is_wall(t_game *game, double x, double y);
int			has_wall_at(t_game *game, double x, double y);
void		put_pixel(t_game *game, int x, int y, int color);
int			create_rgb(int r, int g, int b);

/* ---- Input handling ---- */
int			handle_keypress(int keycode, t_game *game);
int			handle_keyrelease(int keycode, t_game *game);
void		toggle_fullscreen(t_game *game);
void		init_fullscreen(t_game *game);
void		apply_keypress(int keycode, t_game *game);
void		apply_keyrelease(int keycode, t_game *game);

/* ---- Cleanup ---- */
int			cleanup_and_exit(t_game *game);
void		free_game_data(t_game *game);
void		init_game_struct(t_game *game);

/* ---- Test functions ---- */
void		create_test_config(t_config *config);

/* ---- Mouse handling ---- */
void		handle_mouse_look(t_game *game);
int			handle_mousemove(int x, int y, t_game *game);

#endif
