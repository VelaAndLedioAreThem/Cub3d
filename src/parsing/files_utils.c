/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurmish < ldurmish@student.42wolfsburg.d  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 20:45:53 by ldurmish          #+#    #+#             */
/*   Updated: 2025/09/10 22:21:42 by ldurmish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

int	grow_array(char ***arr, int *capacity, int n)
{
	char	**old;
	char	**new;
	int		i;

	old = *arr;
	*capacity *= 2;
	new = (char **)malloc(sizeof(char *) * (*capacity));
	if (!new)
		return (1);
	i = 0;
	while (i < n)
	{
		new[i] = old[i];
		i++;
	}
	free(old);
	*arr = new;
	return (0);
}

char	**read_all_line(int fd, int *output)
{
	char	**arr;
	char	*line;
	int		capacity;
	int		n;

	capacity = 32;
	n = 0;
	arr = (char **)malloc(sizeof(char *) * capacity);
	if (!arr)
		return (NULL);
	line = get_next_line(fd);
	while (line)
	{
		if (n == capacity && grow_array(&arr, &capacity, n))
			return (free(arr), NULL);
		arr[n++] = line;
		line = get_next_line(fd);
	}
	*output = n;
	return (arr);
}

void	free_lines(char **lines, int n)
{
	int		i;

	if (!lines)
		return ;
	i = 0;
	while (i < n)
		free(lines[i++]);
	free(lines);
}
