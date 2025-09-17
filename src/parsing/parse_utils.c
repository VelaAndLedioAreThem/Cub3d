/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurmish < ldurmish@student.42wolfsburg.d  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 20:13:38 by ldurmish          #+#    #+#             */
/*   Updated: 2025/09/16 18:15:21 by ldurmish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

const char	*skip_sapces(const char *s)
{
	if (!s)
		return (NULL);
	while (*s == ' ' || *s == '\t')
		s++;
	return (s);
}

int	is_blank(const char *s)
{
	if (!s)
		return (1);
	while (*s)
	{
		if (*s != ' ' && *s != '\t' && *s != '\n' && *s != '\r')
			return (0);
		s++;
	}
	return (1);
}

void	rtrim_in_place(char *s)
{
	int		len;

	if (!s)
		return ;
	len = (int)ft_strlen(s);
	while (len > 0 && (s[len - 1] == ' ' || s[len - 1] == '\t'
			|| s[len - 1] == '\n' || s[len - 1] == '\r'))
	{
		s[len - 1] = '\0';
		len--;
	}
}

int	looks_like_map_line(const char *s)
{
	int		has_cell;

	if (!s || *s == '\0')
		return (0);
	has_cell = 0;
	while (*s)
	{
		if (*s == CH_WALL || *s == CH_SPACE || *s == CH_N
			|| *s == CH_W || *s == CH_S || *s == CH_E)
			has_cell = 1;
		else if (*s != CH_VOID && *s != '\t')
			return (0);
		s++;
	}
	return (1);
}

const char	*keyreset(const char *s, const char *key)
{
	size_t		i;

	if (!s || !key)
		return (NULL);
	i = 0;
	while (key[i] && s[i] && key[i] == s[i])
		i++;
	if (key[i] != '\0')
		return (NULL);
	s += i;
	while (*s == ' ' || *s == '\t')
		s++;
	return (s);
}
