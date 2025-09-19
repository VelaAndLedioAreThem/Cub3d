/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_identifiers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurmish < ldurmish@student.42wolfsburg.d  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 20:31:10 by ldurmish          #+#    #+#             */
/*   Updated: 2025/09/19 22:58:20 by ldurmish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

static int	id_try_textures(t_identifiers *p, t_config *cfg)
{
	static const char *const	keys[4] = {"NO", "SO", "WE", "EA"};
	static const char *const	dups[4] = {
		"duplciat NO", "duplicate SO", "duplicate WE", "duplicate EA"
	};
	int							i;
	const char					*r;
	int							rc;

	i = -1;
	while (++i < 4)
	{
		r = keyreset(p->s, keys[i]);
		if (!r)
			continue ;
		if (p->seen[i])
			return (perr(P_EDUP, dups[i]));
		p->seen[i] = 1;
		rc = parse_textures(r, i, cfg);
		if (rc != 0)
			return (rc);
		return (1);
	}
	return (0);
}

int	id_try_floor(t_identifiers *p, t_config *cfg)
{
	const char		*r;

	r = keyreset(p->s, "F");
	if (!r)
		return (0);
	if (p->sf)
		return (perr(P_EDUP, "duplicate F"));
	p->sf = 1;
	if (parse_color(r, &cfg->floor) != 0)
		return (perr(P_EFMT, NULL));
	return (1);
}

int	id_check_all(const t_identifiers *p)
{
	if (!p->seen[TEX_NO] || !p->seen[TEX_SO]
		|| !p->seen[TEX_WE] || !p->seen[TEX_EA])
		return (perr(P_EMISS, "missing texture id"));
	if (!p->sf || !p->sc)
		return (perr(P_EMISS, "missing F/C color"));
	return (0);
}

int	id_proccess_line(t_identifiers *p, int i, int *consumed, t_config *cfg)
{
	int			pre;

	pre = id_precheck(p->s, i, consumed);
	if (pre == 1)
		return (*consumed = i + i, 1);
	if (pre == 2)
		return (2);
	p->rc = id_try_textures(p, cfg);
	if (p->rc < 0)
		return (p->rc);
	if (p->rc > 0)
		return (*consumed = i + 1, 1);
	p->rc = id_try_floor(p, cfg);
	if (p->rc < 0)
		return (p->rc);
	if (p->rc > 0)
		return (*consumed = i + 1, 1);
	p->rc = id_try_ceil(p, cfg);
	if (p->rc < 0)
		return (p->rc);
	if (p->rc > 0)
		return (*consumed = i + 1, 1);
	return (perr(P_EFMT, "unknown identifier line"));
}

int	parse_identifiers(char **lines, int n, int *consumed, t_config *cfg)
{
	int					i;
	t_identifiers		parse;
	int					pre;

	parse = (t_identifiers){{0, 0, 0, 0}, 0, 0, NULL, -1};
	if (!lines || !cfg || !consumed)
		return (perr(P_EARG, "parse_identifiers: bad args"));
	i = -1;
	while (++i < n)
	{
		parse.s = skip_spaces(lines[i]);
		pre = id_proccess_line(&parse, i, consumed, cfg);
		if (pre == 1)
			continue ;
		if (pre == 2)
			break ;
		if (pre < 0)
			return (pre);
	}
	if (*consumed == 0)
		*consumed = i;
	return (id_check_all(&parse));
}
