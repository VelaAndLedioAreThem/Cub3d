/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurmish < ldurmish@student.42wolfsburg.d  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 20:25:32 by ldurmish          #+#    #+#             */
/*   Updated: 2025/09/10 21:17:35 by ldurmish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

int	has_cub_ext(const char *path)
{
	size_t		len;

	if (!path)
		return (0);
	len = 0;
	while (path[len])
		len++;
	return (len >= 4 && path[len - 4] == '.' && path[len - 3] == 'c'
		&& path[len - 2] == 'u' && path[len - 1] == 'b');
}

char	**load_files(const char *path, int *n)
{
	int		fd;
	char	**lines;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		perr(P_EOPEN, "cannot open file");
		return (NULL);
	}
	lines = read_all_line(fd, n);
	close(fd);
	if (!lines)
	{
		perr(P_EREAD, "failed to read file");
		return (NULL);
	}
	return (lines);
}

int	parse_config(const char *path, t_config *out)
{
	char	**lines;
	int		n;
	int		ret;

	if (!path || !out)
		return (perr(P_EARG, "Usage ./cub3d <file.cub>"));
	if (!has_cub_ext(path))
		return (perr(P_EARG, "file must end with .cub"));
	lines = load_files(path, &n);
	if (!lines)
		return (1);
	ret = 0;
	return (ret);
}
