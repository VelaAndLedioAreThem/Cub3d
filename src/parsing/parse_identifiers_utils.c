/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_identifiers_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurmish < ldurmish@student.42wolfsburg.d  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 22:11:00 by ldurmish          #+#    #+#             */
/*   Updated: 2025/09/19 23:00:48 by ldurmish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

int	id_precheck(const char *s, int i, int *consumed)
{
	const char	*p;

	(void)i;
	(void)consumed;
	if (!s || !consumed)
		return (perr(P_EARG, "id_precheck: bad args"));
	p = s;
	while (*p == ' ' || *p == '\t')
		p++;
	if (*p == '\0' || *p == '\n' || *p == '\r')
		return (1);
	if (looks_like_map_line(s))
		return (2);
	return (0);
}

const char	*skip_spaces(const char *s)
{
	if (!s)
		return (NULL);
	while (*s == ' ' || *s == '\t')
		s++;
	return (s);
}

int	id_try_ceil(t_identifiers *p, t_config *cfg)
{
	const char	*r;

	r = keyreset(p->s, "C");
	if (!r)
		return (0);
	if (p->sc)
		return (perr(P_EDUP, "duplicate C"));
	p->sc = 1;
	if (parse_color(r, &cfg->ceil) != 0)
		return (perr(P_EFMT, NULL));
	return (1);
}
