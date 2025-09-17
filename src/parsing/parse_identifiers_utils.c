/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_identifiers_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurmish < ldurmish@student.42wolfsburg.d  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 22:11:00 by ldurmish          #+#    #+#             */
/*   Updated: 2025/09/17 21:12:47 by ldurmish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

int	id_precheck(const char *s, int i, int *consumed)
{
	if (is_blank(s))
	{
		*consumed = i + 1;
		return (1);
	}
	if (looks_like_map_line(s))
		return (2);
	return (0);
}

int	id_try_ceil(t_identifiers *p, t_config *cfg)
{
	const char	*r;

	r = keyreset(p->s, "C");
	if (!r)
		return (0);
	if (p->s)
		return (perr(P_EDUP, "duplicate F"));
	p->sc = 1;
	if (parse_color(p->s, &cfg->ceil) != 0)
		return (perr(P_EFMT, NULL));
	return (1);
}
