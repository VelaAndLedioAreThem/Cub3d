/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_identifiers_utils_1.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurmish < ldurmish@student.42wolfsburg.d  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 19:53:55 by ldurmish          #+#    #+#             */
/*   Updated: 2025/09/24 20:57:26 by ldurmish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

void	rstrip_crlf(char *s)
{
	size_t		len;

	if (!s)
		return ;
	len = ft_strlen(s);
	while (len > 0)
	{
		if (s[len - 1] == '\n' || s[len - 1] == '\r')
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

void	normalize_line(char *s, int is_first)
{
	if (!s)
		return ;
	if (is_first)
		strip_utf8_boom(s);
	rstrip_crlf(s);
	tabs_to_space(s);
}
