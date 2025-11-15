/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_rendering.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 00:03:10 by zbabic            #+#    #+#             */
/*   Updated: 2025/11/15 02:13:20 by zbabic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	reset_background(t_env *env)
{
	int	x;
	int	y;

	x = -1;
	while (++x < env->win_width)
	{
		y = -1;
		while (++y < env->win_height)
			mlx_put_pixel(env->img, x, y, COLOR_BACKGROUND);
	}
}

void	render_scene(t_env *env)
{
	reset_background(env);
	// TODO: Draw ceiling/floor
	// TODO: Raycast and draw walls
	// - change first to cast_all_rays and then
	// draw minimap when we change to "3d"
	draw_minimap(env);
	render_all_rays(env, (int)(env->win_width / RES));
}
