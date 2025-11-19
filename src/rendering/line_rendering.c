/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_rendering.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkau <eberkau@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 17:08:15 by zbabic            #+#    #+#             */
/*   Updated: 2025/11/19 18:12:46 by eberkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	calculate_step(int starting_point, int ending_point)
{
	if (ending_point >= starting_point)
		return (1);
	else
		return (-1);
}

static void	draw_line_lower_slope(t_env *env, t_point *starting,
		t_point *ending, int color)
{
	t_point	d;
	t_point	step;
	t_point	line;
	int		p;
	int		i;

	i = 0;
	d.x = abs(ending->x - starting->x);
	d.y = abs(ending->y - starting->y);
	step.x = calculate_step(starting->x, ending->x);
	step.y = calculate_step(starting->y, ending->y);
	p = 2 * d.y - d.x;
	line.x = starting->x;
	line.y = starting->y;
	while (i <= d.x)
	{
		if (line.x >= 0 && line.x < env->win_width && line.y >= 0
			&& line.y < env->win_height)
			mlx_put_pixel(env->img, line.x, line.y, color);
		line.x += step.x;
		p += 2 * d.y - ((p >= 0) * (2 * d.x));
		line.y += ((p >= 0) * step.y);
		++i;
	}
}

static void	draw_line_higher_slope(t_env *env, t_point *starting,
		t_point *ending, int color)
{
	t_point	d;
	t_point	step;
	t_point	line;
	int		p;
	int		i;

	i = 0;
	d.x = abs(ending->x - starting->x);
	d.y = abs(ending->y - starting->y);
	step.x = calculate_step(starting->x, ending->x);
	step.y = calculate_step(starting->y, ending->y);
	p = 2 * d.x - d.y;
	line.x = starting->x;
	line.y = starting->y;
	while (i <= d.y)
	{
		if (line.x >= 0 && line.x < env->win_width && line.y >= 0
			&& line.y < env->win_height)
			mlx_put_pixel(env->img, line.x, line.y, color);
		line.y += step.y;
		p += 2 * d.x - ((p >= 0) * (2 * d.y));
		line.x += ((p >= 0) * step.x);
		++i;
	}
}

/// @brief Draw line on the raster screen using Bresenham's algorithm
/// @param map map
/// @param fir first dot coordinate
/// @param sec second dot coordinate
/// @param cnt counter for x and y
void	draw_line(t_env *env, t_point *starting, t_point *ending, int color)
{
	int	dx;
	int	dy;

	dx = abs(ending->x - starting->x);
	dy = abs(ending->y - starting->y);
	if (dx >= dy)
		draw_line_lower_slope(env, starting, ending, color);
	else
		draw_line_higher_slope(env, starting, ending, color);
}
