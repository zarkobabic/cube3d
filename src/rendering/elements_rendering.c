/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements_rendering.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkau <eberkau@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 12:06:07 by zbabic            #+#    #+#             */
/*   Updated: 2025/12/06 04:37:08 by eberkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_circle_lines(const t_env *env, const t_point *center,
	const t_point *iterator, int color)
{
	int	i;

	i = center->x - iterator->x;
	while (i <= center->x + iterator->x)
	{
		mlx_put_pixel(env->img, i, center->y + iterator->y, color);
		mlx_put_pixel(env->img, i, center->y - iterator->y, color);
		++i;
	}
	i = center->x - iterator->y;
	while (i <= center->x + iterator->y)
	{
		mlx_put_pixel(env->img, i, center->y + iterator->x, color);
		mlx_put_pixel(env->img, i, center->y - iterator->x, color);
		++i;
	}
}

void	draw_filled_circle(const t_env *env,
	const t_point_double *center_double, int radius, int color)
{
	t_point	center;
	t_point	iterator;
	int		d;

	center.x = (int)center_double->x;
	center.y = (int)center_double->y;
	iterator.x = 0;
	iterator.y = radius;
	d = 3 - 2 * radius;
	while (iterator.y >= iterator.x)
	{
		draw_circle_lines(env, &center, &iterator, color);
		++iterator.x;
		if (d > 0)
		{
			--iterator.y;
			d = d + 4 * (iterator.x - iterator.y) + 10;
		}
		else
			d = d + 4 * iterator.x + 6;
	}
}

void	draw_square(const t_env *env, int size, const t_point *left_corner,
		unsigned int color)
{
	int	x;
	int	y;

	y = left_corner->y;
	while (y < left_corner->y + size)
	{
		x = left_corner->x;
		while (x < left_corner->x + size)
		{
			mlx_put_pixel(env->img, x, y, color);
			++x;
		}
		++y;
	}
}
