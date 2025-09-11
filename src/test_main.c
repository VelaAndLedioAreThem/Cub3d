/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vszpiech < vszpiech@student.42wolfsburg.d  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 10:00:00 by vszpiech          #+#    #+#             */
/*   Updated: 2025/09/11 10:00:00 by vszpiech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/execution.h"

void	create_test_config(t_config *config);

int	main(void)
{
	t_config	cfg;
	t_game		game;

	printf("🧪 Starting Cub3D Test Mode\n");
	printf("   Creating test configuration...\n");
	
	create_test_config(&cfg);
	
	printf("   Map size: %dx%d\n", cfg.map.width, cfg.map.height);
	printf("   Player position: (%d, %d) facing %c\n", 
		cfg.player.x, cfg.player.y, cfg.player.dir);
	printf("   Floor color: RGB(%d, %d, %d)\n", 
		cfg.floor.r, cfg.floor.g, cfg.floor.b);
	printf("   Ceiling color: RGB(%d, %d, %d)\n", 
		cfg.ceil.r, cfg.ceil.g, cfg.ceil.b);
	
	printf("   Initializing game...\n");
	init_game(&game, &cfg);
	
	printf("   Setting up input hooks...\n");
	setup_hooks(&game);
	
	printf("🎮 Test mode ready! Use WASD to move, arrows to turn, ESC to exit\n");
	printf("   Map layout:\n");
	for (int i = 0; i < cfg.map.height; i++)
		printf("   %s\n", cfg.map.grid[i]);
	
	mlx_loop(game.mlx);
	
	destroy_configs(&cfg);
	return (0);
}