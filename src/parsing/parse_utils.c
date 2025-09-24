/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurmish < ldurmish@student.42wolfsburg.d  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 20:13:38 by ldurmish          #+#    #+#             */
/*   Updated: 2025/09/22 16:28:39 by ldurmish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

int	is_blank(const char *s)
{
	if (!s)
		return (1);
	while (*s)
	{
		if (*s == ' ' || *s == '\t' || *s == '\n' || *s == '\r')
		{
			s++;
			continue ;
		}
		if (*s == '\\' && (s[1] == 'r' || s[1] == 'n'))
		{
			s += 2;
			continue ;
		}
		return (0);
	}
	return (1);
}

void	rtrim_in_place(char *s)
{
	size_t		len;

	if (!s)
		return ;
	len = ft_strlen(s);
	while (len > 0)
	{
		if (s[len - 1] == ' ' || s[len - 1] == '\t'
			|| s[len - 1] == '\n' || s[len - 1] == '\r')
		{
			s[--len] = '\0';
			continue ;
		}
		if (len >= 2 && s[len - 2] == '\\'
			&& (s[len - 1] == 'r' || s[len - 1] == 'n'))
		{
			len -= 2;
			s[len] = '\0';
			continue ;
		}
		break ;
	}
}

int	looks_like_map_line(const char *s)
{
	int		has_cell;

	has_cell = 0;
	s = skip_spaces(s);
	if (!s || *s == '\0')
		return (0);
	while (*s)
	{
		if (*s == '\n' || *s == '\r')
			break ;
		if (!(*s == CH_WALL || *s == CH_SPACE || *s == CH_VOID
				|| *s == CH_N || *s == CH_W || *s == CH_S || *s == CH_E))
			return (0);
		if (*s != CH_VOID && *s != '\t')
			has_cell = 1;
		s++;
	}
	return (has_cell);
}

const char	*keyreset(const char *s, const char *key)
{
	size_t		i;
	const char	*p;

	p = skip_spaces(s);
	if (!p || !key)
		return (NULL);
	i = 0;
	while (key[i] && key[i] == p[i])
		i++;
	if (key[i] != '\0')
		return (NULL);
	p += i;
	while (*p == ' ' || *p == '\t')
		p++;
	return (p);
}
