/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurmish < ldurmish@student.42wolfsburg.d  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 21:06:45 by ldurmish          #+#    #+#             */
/*   Updated: 2025/09/25 13:16:04 by ldurmish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

static void	skip_leading_ws(const char **str)
{
	const char		*p;

	if (!str || !*str)
		return ;
	p = *str;
	while (*p == ' ' || *p == '\t')
		p++;
	*str = p;
}

static int	read_component(const char **str, int *color)
{
	const char	*p;
	int			val;

	if (!str || !*str || !color)
		return (perr(P_EARG, "read_component bad args"));
	p = *str;
	if (!ft_isdigit((unsigned char)*p))
		return (perr(P_EFMT, "expected color number"));
	val = 0;
	while (*p && ft_isdigit((unsigned char)*p))
	{
		val = val * 10 + (*p - '0');
		if (val < 0 || val > 255)
			return (perr(P_EFMT, "color out of range"));
		p++;
	}
	*color = val;
	*str = p;
	return (0);
}

static int	expect_comma(const char **str)
{
	const char		*p;

	if (!str || !*str)
		return (perr(P_EARG, "expect_comma bad args"));
	p = *str;
	skip_leading_ws(&p);
	if (*p != ',')
		return (perr(P_EFMT, "expected comma"));
	p++;
	skip_leading_ws(&p);
	*str = p;
	return (0);
}

int	parse_rgb_triplet(const char *s, int *r, int *g, int *b)
{
	const char	*p;

	if (!s || !r || !g || !b)
		return (perr(P_EARG, "parse_rgb_triplet bad args"));
	p = s;
	skip_leading_ws(&p);
	if (read_component(&p, r) != 0)
		return (1);
	if (expect_comma(&p) != 0)
		return (1);
	if (read_component(&p, g) != 0)
		return (1);
	if (expect_comma(&p) != 0)
		return (1);
	if (read_component(&p, b) != 0)
		return (1);
	skip_leading_ws(&p);
	if (*p != '\0' && *p != '\n' && *p != '\r')
		return (perr(P_EFMT, "trailing characters after color"));
	return (0);
}

int	parse_color(const char *s, t_color *dst)
{
	int		r;
	int		g;
	int		b;

	if (!dst)
		return (perr(P_EARG, "parse_color bad arg"));
	if (parse_rgb_triplet(s, &r, &g, &b) != 0)
		return (1);
	dst->r = r;
	dst->g = g;
	dst->b = b;
	dst->value = ((r & 0xFF) << 16 | (g & 0xFF) << 8 | (b & 0xFF));
	return (0);
}
