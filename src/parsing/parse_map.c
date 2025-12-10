/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurmish < ldurmish@student.42wolfsburg.d  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 21:22:01 by ldurmish          #+#    #+#             */
/*   Updated: 2025/09/24 22:31:16 by ldurmish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

static void	map_detect_bounds(char **line, int n, t_parse_map *map, int *width)
{
	int		i;
	int		len;

	*width = 0;
	i = map->start;
	while (i < n && !is_blank_line(line[i]))
	{
		len = (int)rtrim_len(line[i]);
		if (len > *width)
			*width = len;
		i++;
	}
	map->end = i;
}

int	map_skip_blank_start(char **lines, int n)
{
	int		i;

	i = 0;
	while (i < n && is_blank_line(lines[i]))
		i++;
	return (i);
}

int	map_alloc_grid(t_map *map)
{
	int		i;

	if (!map || map->height <= 0 || map->width <= 0)
		return (-1);
	map->grid = (char **)malloc(sizeof(char *) * map->height);
	if (!map->grid)
		return (-1);
	i = 0;
	while (i < map->height)
	{
		map->grid[i] = (char *)malloc((size_t)map->width + 1);
		if (!map->grid[i])
		{
			while (i > 0)
				free(map->grid[--i]);
			free(map->grid);
			map->grid = NULL;
			return (-1);
		}
		i++;
	}
	return (0);
}

int	map_fill_grid(char **lines, t_parse_map *p_map, t_map *map,
				t_player *player)
{
	int			y;
	int			pc;
	t_row_map	row;

	pc = 0;
	y = 0;
	while (y < map->height)
	{
		row.src = lines[p_map->start + y];
		row.dst = map->grid[y];
		row.width = map->width;
		row.y = y;
		row.player = player;
		row.pc = &pc;
		if (fill_row_chars(&row) != 0)
			return (-1);
		y++;
	}
	return (check_player_count(pc));
}

int	parse_map(char **lines, int n, t_map *map, t_player *player)
{
	t_parse_map		p_map;
	int				row_count;

	if (!map || !player)
		return (perr(P_EARG, "parse_map: bad args"));
	if (!lines || n <= 0)
		return (perr(P_EMISS, "missing map section"));
	*map = (t_map){NULL, 0, 0};
	*player = (t_player){0.0, 0.0, 0};
	p_map.start = map_skip_blank_start(lines, n);
	if (p_map.start >= n)
		return (perr(P_EMISS, "missing map section"));
	map_detect_bounds(lines, n, &p_map, &map->width);
	map->height = p_map.end - p_map.start;
	if (map->height <= 0 || map->width <= 0)
		return (perr(P_EFMT, "invalid map size"));
	if (map_alloc_grid(map) != 0)
		return (perr(P_EINVAL, "failed to allocate map grid"));
	row_count = map_fill_grid(lines, &p_map, map, player);
	if (row_count != 0)
		return (row_count);
	return (0);
}
