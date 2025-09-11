/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vszpiech < vszpiech@student.42wolfsburg.d  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 10:00:00 by vszpiech          #+#    #+#             */
/*   Updated: 2025/09/11 10:00:00 by vszpiech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

int	is_wall(t_game *game, double x, double y)
{
	int	map_x, map_y;
	
	if (x < 0 || x >= game->config->map.width * TILE_SIZE || 
		y < 0 || y >= game->config->map.height * TILE_SIZE)
		return (1);
	
	map_x = (int)(x / TILE_SIZE);
	map_y = (int)(y / TILE_SIZE);
	
	return (game->config->map.grid[map_y][map_x] == CH_WALL);
}

int	has_wall_at(t_game *game, double x, double y)
{
	return (is_wall(game, x, y));
}

void	load_textures(t_game *game)
{
	int	i;
	
	for (i = 0; i < TEX_COUNT; i++)
	{
		if (game->config->tex.path[i])
		{
			game->textures[i].img = mlx_xpm_file_to_image(game->mlx, 
				game->config->tex.path[i], &game->textures[i].width, 
				&game->textures[i].height);
			if (game->textures[i].img)
			{
				game->textures[i].addr = mlx_get_data_addr(game->textures[i].img,
					&game->textures[i].bits_per_pixel,
					&game->textures[i].line_length,
					&game->textures[i].endian);
			}
		}
	}
}

/**
 * put_pixel - Put a pixel with given color to the image buffer
 * @game: Game structure containing image data
 * @x: X coordinate of pixel
 * @y: Y coordinate of pixel  
 * @color: Color in RGB format (0x00RRGGBB)
 * 
 * This function directly manipulates the image buffer to set pixel colors.
 */
void	put_pixel(t_game *game, int x, int y, int color)
{
	char	*dst;
	
	// Check bounds to prevent buffer overflow
	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
		return ;
	
	// Calculate memory address for this pixel
	dst = game->img_addr + (y * game->line_length + x * (game->bits_per_pixel / 8));
	
	// Write color to memory (assuming 32-bit color depth)
	*(unsigned int*)dst = color;
}

/**
 * create_rgb - Create RGB color value from individual components
 * @r: Red component (0-255)
 * @g: Green component (0-255)  
 * @b: Blue component (0-255)
 * 
 * Combines RGB components into a single integer suitable for put_pixel().
 * Format: 0x00RRGGBB
 * 
 * Return: Combined RGB color value
 */
int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	free_game_data(t_game *game)
{
	int	i;
	
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	
	for (i = 0; i < TEX_COUNT; i++)
	{
		if (game->textures[i].img)
			mlx_destroy_image(game->mlx, game->textures[i].img);
	}
	
	if (game->window)
		mlx_destroy_window(game->mlx, game->window);
	
	if (game->mlx)
		mlx_destroy_display(game->mlx);
}