/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurmish < ldurmish@student.42wolfsburg.d  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 16:21:37 by ldurmish          #+#    #+#             */
/*   Updated: 2025/09/10 20:11:03 by ldurmish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/parsing.h"
#include "../include/execution.h"

int	main(int ac, char **av)
{
	t_config	cfg;
	t_game		game;

	init_configs(&cfg);
	if (ac != 2)
		return (perr(P_EARG, "Usage: ./cub3d <file.cub>"));
	if (parse_config(av[1], &cfg) != 0)
		return (destroy_configs(&cfg), 1);
	
	init_game(&game, &cfg);
	setup_hooks(&game);
	mlx_loop(game.mlx);
	
	destroy_configs(&cfg);
	return (0);
}
