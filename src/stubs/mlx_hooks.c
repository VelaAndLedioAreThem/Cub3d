/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vela <vela@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 13:08:12 by vela              #+#    #+#             */
/*   Updated: 2025/09/26 13:08:12 by vela             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

int	mlx_loop(void *mlx_ptr)
{
	(void)mlx_ptr;
	return (0);
}

int	mlx_hook(void *win_ptr, int x_event, int x_mask, void *param)
{
	int	(*funct)(void);

	(void)win_ptr;
	(void)x_event;
	(void)x_mask;
	funct = (int (*)(void))param;
	(void)funct;
	return (0);
}

int	mlx_loop_hook(void *mlx_ptr, void *param1, void *param2)
{
	int	(*funct)(void);

	(void)mlx_ptr;
	funct = (int (*)(void))param1;
	(void)funct;
	(void)param2;
	return (0);
}
