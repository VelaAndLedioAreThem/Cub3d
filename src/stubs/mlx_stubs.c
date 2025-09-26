/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_stubs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vszpiech <vszpiech@student.42.fr>              +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 10:00:00 by vszpiech          #+#    #+#             */
/*   Updated: 2025/09/11 16:37:16 by vszpiech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

void	*mlx_init(void)
{
	return ((void *)1);
}

void	*mlx_new_window(void *mlx_ptr, int size_x, int size_y, char *title)
{
	(void)mlx_ptr;
	(void)size_x;
	(void)size_y;
	(void)title;
	return ((void *)1);
}

void	*mlx_new_image(void *mlx_ptr, int width, int height)
{
	(void)mlx_ptr;
	(void)width;
	(void)height;
	return ((void *)1);
}

char	*mlx_get_data_addr(void *img_ptr, int *bits_per_pixel, int *size_line,
		int *endian)
{
	static char	dummy_buffer[1920 * 1080 * 4];

	(void)img_ptr;
	*bits_per_pixel = 32;
	*size_line = 1920 * 4;
	*endian = 0;
	return (dummy_buffer);
}

int	mlx_put_image_to_window(void *mlx_ptr, void *win_ptr,
				void *img_ptr, ...)
{
	(void)mlx_ptr;
	(void)win_ptr;
	(void)img_ptr;
	return (0);
}
