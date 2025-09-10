/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurmish < ldurmish@student.42wolfsburg.d  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 20:45:53 by ldurmish          #+#    #+#             */
/*   Updated: 2025/09/10 21:56:13 by ldurmish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

char	**read_all_line(int fd, int *output)
{
	char	**arr;
	char	*line;
	int		space;
	int		n;

	space = 32;
	n = 0;
	arr = (char **)malloc(sizeof(char *) * space);
	if (!arr)
		return (NULL);
	line = get_next_line(fd);
}
