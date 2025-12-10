/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_math.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vszpiech                                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 23:41:00 by vszpiech          #+#    #+#             */
/*   Updated: 2025/09/25 23:41:00 by vszpiech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

double	normalize_angle(double angle)
{
	while (angle >= TWO_PI)
		angle -= TWO_PI;
	while (angle < 0)
		angle += TWO_PI;
	return (angle);
}

double	distance_between_points(double x1, double y1, double x2, double y2)
{
	double	dx;
	double	dy;

	dx = x2 - x1;
	dy = y2 - y1;
	return (sqrt(dx * dx + dy * dy));
}
