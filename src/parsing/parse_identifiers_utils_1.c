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
	size_t		n;

	if (!s)
		return ;
	n = 0;
	while (s[n])
		n++;
	while (n > 0 && (s[n - 1] == '\n' || s[n - 1] == '\r'))
	{
		s[n - 1] = '\0';
		n--;
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
