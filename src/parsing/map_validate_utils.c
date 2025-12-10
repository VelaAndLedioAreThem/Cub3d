/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vszpiech <vszpiech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 15:32:32 by ldurmish          #+#    #+#             */
/*   Updated: 2025/12/09 23:26:37 by vszpiech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"
#include <linux/limits.h>

int	is_floor(int c)
{
	return (c == '0');
}

int	validate_not_empty_map(t_map *map)
{
	int		x;
	int		y;
	int		seen;

	if (!map || !map->grid || map->height <= 0 || map->width <= 0)
		return (perr(P_EFMT, "empty map"));
	seen = 0;
	y = 0;
	while (y < map->height && !seen)
	{
		x = 0;
		while (x < map->width && !seen)
		{
			if (map->grid[y][x] != ' ')
				seen = 1;
			x++;
		}
		y++;
	}
	if (!seen)
		return (perr(P_EFMT, "map has no content"));
	return (0);
}

int	validate_map_closed(t_map *map)
{
	int			x;
	int			y;

	if (!map || !map->grid)
		return (perr(P_EARG, "validate_map_closed: bad args"));
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (is_floor(map->grid[y][x]))
			{
				if (y == 0 || y == map->height - 1 || x == 0
					|| x == map->width - 1)
					return (perr(P_EFMT, "map not closed (edge)"));
				if (map->grid[y - 1][x] == ' ' || map->grid[y + 1][x] == ' '
					|| map->grid[y][x - 1] == ' ' || map->grid[y][x + 1] == ' ')
					return (perr(P_EFMT, "map not close (void)"));
			}
			x++;
		}
		y++;
	}
	return (0);
}
