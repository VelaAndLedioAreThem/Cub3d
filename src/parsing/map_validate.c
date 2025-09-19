/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurmish < ldurmish@student.42wolfsburg.d  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 21:25:26 by ldurmish          #+#    #+#             */
/*   Updated: 2025/09/19 22:12:02 by ldurmish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

int	is_blank_line(const char *s)
{
	while (*s && (*s == ' ' || *s == '\t'))
		s++;
	return (*s == '\0');
}

size_t	rtrim_len(const char *s)
{
	const char		*end;

	end = s + ft_strlen(s);
	while (end > s && (end[-1] == ' ' || end[-1] == '\t' || end[-1] == '\r'
			|| end[-1] == '\n'))
		end--;
	return ((size_t)(end - s));
}

int	check_player_count(int pc)
{
	if (pc == 1)
		return (0);
	if (pc == 0)
		return (-2);
	return (-3);
}

int	is_map_char(char ch)
{
	return (ch == '0' || ch == '1' || ch == ' ' || ch == 'N'
		|| ch == 'S' || ch == 'E' || ch == 'W');
}

int	fill_row_chars(t_row_map *row)
{
	size_t	len;
	int		x;
	int		ch;

	len = rtrim_len(row->src);
	x = 0;
	while (x < (int)len)
	{
		ch = (unsigned char)row->src[x];
		if (!is_map_char(ch))
			return (-1);
		if (ch == 'N' || ch == 'S' || ch == 'E' || ch == 'W')
		{
			row->player->x = x + 0.5;
			row->player->y = row->y + 0.5;
			row->player->dir = (char)ch;
			(*row->pc)++;
			ch = '0';
		}
		row->dst[x++] = (char)ch;
	}
	while (x < row->width)
		row->dst[x++] = ' ';
	row->dst[row->width] = '\0';
	return (0);
}
