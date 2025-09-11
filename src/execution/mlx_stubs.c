/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_stubs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vszpiech <vszpiech@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 10:00:00 by vszpiech          #+#    #+#             */
/*   Updated: 2025/09/11 16:37:16 by vszpiech           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

/*
 * MLX stub functions for compilation when MLX is not available
 * These are temporary implementations that allow the code to compile
 * but don't provide actual graphics functionality.
 * 
 * Remove this file when MLX library is properly set up.
 */

void *mlx_init(void)
{
	return ((void *)1); // Return non-NULL pointer
}

void *mlx_new_window(void *mlx_ptr, int size_x, int size_y, char *title)
{
	(void)mlx_ptr;
	(void)size_x;
	(void)size_y;
	(void)title;
	return ((void *)1); // Return non-NULL pointer
}

void *mlx_new_image(void *mlx_ptr, int width, int height)
{
	(void)mlx_ptr;
	(void)width;
	(void)height;
	return ((void *)1); // Return non-NULL pointer
}

char *mlx_get_data_addr(void *img_ptr, int *bits_per_pixel, int *size_line, int *endian)
{
	static char dummy_buffer[1920 * 1080 * 4]; // Static buffer for testing
	
	(void)img_ptr;
	*bits_per_pixel = 32;
	*size_line = 1920 * 4;
	*endian = 0;
	return (dummy_buffer);
}

int mlx_put_image_to_window(void *mlx_ptr, void *win_ptr, void *img_ptr, int x, int y)
{
	(void)mlx_ptr;
	(void)win_ptr;
	(void)img_ptr;
	(void)x;
	(void)y;
	return (0);
}

void *mlx_xpm_file_to_image(void *mlx_ptr, char *filename, int *width, int *height)
{
	(void)mlx_ptr;
	(void)filename;
	*width = 64;
	*height = 64;
	return ((void *)1); // Return non-NULL pointer
}

int mlx_loop(void *mlx_ptr)
{
	(void)mlx_ptr;
	// In a real implementation, this would start the event loop
	// For stub purposes, we just return
	ft_printf("MLX loop started (stub implementation)\n");
	return (0);
}

int mlx_hook(void *win_ptr, int x_event, int x_mask, int (*funct)(), void *param)
{
	(void)win_ptr;
	(void)x_event;
	(void)x_mask;
	(void)funct;
	(void)param;
	return (0);
}

int mlx_loop_hook(void *mlx_ptr, int (*funct)(), void *param)
{
	(void)mlx_ptr;
	(void)funct;
	(void)param;
	return (0);
}

int mlx_destroy_image(void *mlx_ptr, void *img_ptr)
{
	(void)mlx_ptr;
	(void)img_ptr;
	return (0);
}

int mlx_destroy_window(void *mlx_ptr, void *win_ptr)
{
	(void)mlx_ptr;
	(void)win_ptr;
	return (0);
}

int mlx_destroy_display(void *mlx_ptr)
{
	(void)mlx_ptr;
	return (0);
}