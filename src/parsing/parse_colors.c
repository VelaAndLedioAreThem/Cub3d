/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurmish < ldurmish@student.42wolfsburg.d  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 21:06:45 by ldurmish          #+#    #+#             */
/*   Updated: 2025/09/16 23:46:34 by ldurmish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

void	skip_ws(const char **str)
{
	const char		*p;

	p = *str;
	while (*p == ' ' || *p == '\t')
		p++;
	*str = p;
}

int	read_num_0_255(const char **str, int *color)
{
	const char		*p;
	int				val;
	int				has_digit;

	p = *str;
	skip_ws(&p);
	val = 0;
	has_digit = 0;
	while (*p && ft_isdigit(*p))
	{
		has_digit = 0;
		val = val * 10 + (*p - '0');
		if (val > 255)
			return (perr(P_EFMT, "color out of range"));
		p++;
	}
	if (!has_digit)
		return (perr(P_EFMT, "expected color number"));
	skip_ws(&p);
	*color = val;
	*str = p;
	return (0);
}

static int	expect_comma(const char **str)
{
	const char	*s;

	s = *str;
	skip_ws(&s);
	if (*s != ',')
		return (perr(P_EFMT, "expect comma"));
	s++;
	skip_ws(&s);
	*str = s;
	return (0);
}

int	parse_rgb_triplet(const char *s, int *r, int *g, int *b)
{
	const char		*p;

	if (!s || !r || !g || !b)
		return (perr(P_EARG, "parse_rgb_triplet bad args"));
	p = s;
	if (read_num_0_255(&p, r) != 0)
		return (1);
	if (expect_comma(&p) != 0)
		return (1);
	if (read_num_0_255(&p, g) != 0)
		return (1);
	if (expect_comma(&p) != 0)
		return (1);
	if (read_num_0_255(&p, b) != 0)
		return (1);
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
