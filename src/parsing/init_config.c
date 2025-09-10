/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurmish < ldurmish@student.42wolfsburg.d  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 16:36:47 by ldurmish          #+#    #+#             */
/*   Updated: 2025/09/10 20:21:28 by ldurmish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

void	init_configs(t_config *config)
{
	int		i;

	if (!config)
		return ;
	i = 0;
	while (i < TEX_COUNT)
		config->tex.path[i++] = NULL;
	config->floor = (t_color){-1, -1, -1, -1};
	config->ceil = (t_color){-1, -1, -1, -1};
	config->map.grid = NULL;
	config->map.width = 0;
	config->map.height = 0;
	config->player = (t_player){-1, -1, 0};
}

void	destroy_configs(t_config *config)
{
	int		i;

	if (!config)
		return ;
	i = 0;
	while (i < TEX_COUNT)
	{
		free(config->tex.path[i]);
		i++;
	}
	if (config->map.grid)
	{
		i = 0;
		while (i < config->map.height)
			free(config->map.grid[++i]);
		free(config->map.grid);
	}
	init_configs(config);
}
