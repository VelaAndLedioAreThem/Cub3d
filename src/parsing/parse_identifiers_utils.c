/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_identifiers_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurmish < ldurmish@student.42wolfsburg.d  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 22:11:00 by ldurmish          #+#    #+#             */
/*   Updated: 2025/09/24 19:53:30 by ldurmish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

int	id_precheck(const char *s, int i, int *consumed)
{
	const char	*p;

	(void)i;
	(void)consumed;
	if (!s || !consumed)
		return (-perr(P_EARG, "id_precheck: bad args"));
	p = s;
	while (*p == ' ' || *p == '\t')
		p++;
	if (*p == '\0' || *p == '\n' || *p == '\r')
		return (1);
	if (looks_like_map_line(s))
		return (2);
	return (0);
}

void	strip_utf8_boom(char *str)
{
	unsigned char	*p;

	if (!str)
		return ;
	p = (unsigned char *)str;
	if (p[0] == 0xEF && p[1] == 0xBB && p[2] == 0xBF)
		ft_memmove(str, str + 3, ft_strlen(str + 3) + 1);
}

void	tabs_to_space(char *s)
{
	int		i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\t')
			s[i] = ' ';
		i++;
	}
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
	int			rc;

	r = keyreset(p->s, "C");
	if (!r)
		return (0);
	if (p->sc)
		return (-perr(P_EDUP, "duplicate C"));
	rc = parse_color(r, &cfg->ceil);
	if (rc != 0)
		return (-rc);
	p->sc = 1;
	return (1);
}
