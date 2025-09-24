/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurmish < ldurmish@student.42wolfsburg.d  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 16:22:41 by ldurmish          #+#    #+#             */
/*   Updated: 2025/09/24 20:57:42 by ldurmish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "cub3d.h"

typedef enum e_perr
{
	P_OK = 0,
	P_EARG,
	P_EOPEN,
	P_EREAD,
	P_EFMT,
	P_EDUP,
	P_EMISS,
	P_EINVAL,
	P_EMAP
}	t_perr;

typedef struct s_identifiers
{
	int			seen[4];
	int			sf;
	int			sc;
	const char	*s;
	int			rc;
}	t_identifiers;

typedef struct s_parse_map
{
	int		start;
	int		end;
	int		player_count;
}	t_parse_map;

typedef struct s_row_map
{
	const char		*src;
	char			*dst;
	int				width;
	int				y;
	t_player		*player;
	int				*pc;
}	t_row_map;

int			parse_config(const char *path, t_config *out);
int			perr(t_perr code, const char *msg);
char		**read_all_line(int fd, int *output);
void		free_lines(char **lines, int n);
const char	*keyreset(const char *s, const char *key);
int			looks_like_map_line(const char *s);
void		rtrim_in_place(char *s);
int			is_blank(const char *s);
const char	*skip_spaces(const char *s);
int			parse_identifiers(char **lines, int n,
				int *consumed, t_config *cfg);;
int			id_precheck(const char *s, int i, int *consumed);
int			parse_textures(const char *r, int which, t_config *cfg);
int			parse_color(const char *s, t_color *dst);
int			id_try_ceil(t_identifiers *p, t_config *cfg);
int			parse_map(char **lines, int n, t_map *map, t_player *player);
int			is_blank_line(const char *s);
size_t		rtrim_len(const char *s);
int			check_player_count(int pc);
int			fill_row_chars(t_row_map *row);
int			validate_map_closed(t_map *map);
int			validate_not_empty_map(t_map *map);
void		rstrip_crlf(char *s);
void		strip_utf8_boom(char *str);
void		tabs_to_space(char *s);
void		normalize_line(char *s, int is_first);
#endif
