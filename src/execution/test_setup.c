/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vszpiech < vszpiech@student.42wolfsburg.d  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 10:00:00 by vszpiech          #+#    #+#             */
/*   Updated: 2025/09/11 10:00:00 by vszpiech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

void	create_test_map(t_config *config)
{
	config->map.height = 10;
	config->map.width = 15;
	
	config->map.grid = malloc(sizeof(char *) * config->map.height);
	
	config->map.grid[0] = ft_strdup("111111111111111");
	config->map.grid[1] = ft_strdup("100000000000001");
	config->map.grid[2] = ft_strdup("100000000000001");
	config->map.grid[3] = ft_strdup("100000111000001");
	config->map.grid[4] = ft_strdup("100000101000001");
	config->map.grid[5] = ft_strdup("100000000000001");
	config->map.grid[6] = ft_strdup("100001111100001");
	config->map.grid[7] = ft_strdup("100000000000001");
	config->map.grid[8] = ft_strdup("100000000000001");
	config->map.grid[9] = ft_strdup("111111111111111");
}

void	setup_test_textures(t_config *config)
{
	config->tex.path[TEX_NO] = ft_strdup("textures/north.xpm");
	config->tex.path[TEX_SO] = ft_strdup("textures/south.xpm");
	config->tex.path[TEX_EA] = ft_strdup("textures/east.xpm");
	config->tex.path[TEX_WE] = ft_strdup("textures/west.xpm");
}

void	setup_test_colors(t_config *config)
{
	config->floor.r = 64;
	config->floor.g = 64;
	config->floor.b = 64;
	config->floor.value = create_rgb(64, 64, 64);
	
	config->ceil.r = 128;
	config->ceil.g = 128;
	config->ceil.b = 128;
	config->ceil.value = create_rgb(128, 128, 128);
}

void	setup_test_player(t_config *config)
{
	config->player.x = 7;
	config->player.y = 5;
	config->player.dir = CH_N;
}

void	create_test_config(t_config *config)
{
	init_configs(config);
	create_test_map(config);
	setup_test_textures(config);
	setup_test_colors(config);
	setup_test_player(config);
}