/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurmish < ldurmish@student.42wolfsburg.d  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 19:50:34 by ldurmish          #+#    #+#             */
/*   Updated: 2025/09/16 20:38:48 by ldurmish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

char	*dup_trim(const char *str)
{
	const char		*a;
	const char		*b;
	size_t			len;
	char			*res;

	if (!str)
		return (NULL);
	a = str;
	while (*a == ' ' || *a == '\t')
		a++;
	b = a + ft_strlen(a);
	while (b > a && (b[-1] == ' ' || b[-1] == '\t' || b[-1] == '\r'
			|| b[-1] == '\n'))
		b--;
	len = (size_t)(b - a);
	res = (char *)malloc(len + 1);
	if (!res)
		return (NULL);
	ft_memcpy(res, a, len);
	res[len] = '\0';
	return (res);
}

static int	has_ext(const char *path, const char *exit)
{
	size_t		path_len;
	size_t		exit_len;

	if (!path || !exit)
		return (0);
	path_len = ft_strlen(path);
	exit_len = ft_strlen(exit);
	if (path_len < exit_len)
		return (0);
	return (ft_strncmp(path + (path_len - exit_len), exit, exit_len) == 0);
}

static int	valid_texture_path(const char *path)
{
	if (has_ext(path, ".xpm"))
		return (1);
	return (0);
}

int	parse_textures(const char *str, int which, t_config *cfg)
{
	char	*path;
	int		fd;

	if (!str || !cfg)
		return (perr(P_EARG, "parse_textures: bad args"));
	if (which < 0 || which >= TEX_COUNT)
		return (perr(P_EARG, "parse_textures: invalid id"));
	path = dup_trim(str);
	if (!path || path[0] == '\0')
		return (free(path), perr(P_EFMT, "empty texture path"));
	if (!valid_texture_path(path))
		return (free(path), perr(P_EFMT, "texture must be .xpm"));
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (free(path), perr(P_EOPEN, "cannot open texture file"));
	close (fd);
	if (cfg->tex.path[which])
	{
		free(cfg->tex.path[which]);
		cfg->tex.path[which] = NULL;
	}
	cfg->tex.path[which] = path;
	return (0);
}
