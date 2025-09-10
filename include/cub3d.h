/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurmish < ldurmish@student.42wolfsburg.d  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 17:04:26 by ldurmish          #+#    #+#             */
/*   Updated: 2025/09/10 21:32:57 by ldurmish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/time.h>
# include <stdio.h>
# include "../lib/libft/include/libft.h"

/* ---- Textures identifiers ---- */
# define TEX_NO 0
# define TEX_SO 1
# define TEX_WE 2
# define TEX_EA 3
# define TEX_COUNT 4

/* ---- Map cherset ---- */
# define CH_WALL	'1'
# define CH_SPACE	'0'
# define CH_VOID	' '
# define CH_N		'N'
# define CH_S		'S'
# define CH_W		'W'
# define CH_E		'E'

/* ---- Texture paths ---- */
typedef struct s_textures
{
	char	*path[TEX_COUNT];
}	t_textures;

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
	int		value;
}	t_color;

typedef struct s_map
{
	char	**grid;
	int		height;
	int		width;
}	t_map;

typedef struct s_player
{
	int		x;
	int		y;
	char	dir;
}	t_player;

typedef struct s_config
{
	t_textures	tex;
	t_color		floor;
	t_color		ceil;
	t_map		map;
	t_player	player;
}	t_config;

void	init_configs(t_config *config);
void	destroy_configs(t_config *config);

#endif
