/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_destroy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vela <vela@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 13:08:03 by vela              #+#    #+#             */
/*   Updated: 2025/09/26 13:08:03 by vela             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

int	mlx_destroy_image(void *mlx_ptr, void *img_ptr)
{
	(void)mlx_ptr;
	(void)img_ptr;
	return (0);
}

int	mlx_destroy_window(void *mlx_ptr, void *win_ptr)
{
	(void)mlx_ptr;
	(void)win_ptr;
	return (0);
}

int	mlx_destroy_display(void *mlx_ptr)
{
	(void)mlx_ptr;
	return (0);
}

void	*mlx_xpm_file_to_image(void *mlx_ptr, char *filename, int *width,
		int *height)
{
	(void)mlx_ptr;
	(void)filename;
	*width = 64;
	*height = 64;
	return ((void *)1);
}
