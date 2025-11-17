/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_rendering.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 00:03:10 by zbabic            #+#    #+#             */
/*   Updated: 2025/11/17 14:58:38 by zbabic           ###   ########.fr       */
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


void	render_floor(t_env *env, t_point *wall_end)
{
	t_point	screen_bottom_edge;

	screen_bottom_edge.y = env->win_height;
	screen_bottom_edge.x = wall_end->x;
	draw_line(env, wall_end, &screen_bottom_edge, env->map.floor_color);
}

void	render_ceiling(t_env *env, t_point *wall_start)
{
	t_point	screen_top_edge;

	screen_top_edge.y = 0;
	screen_top_edge.x = wall_start->x;
	draw_line(env, &screen_top_edge, wall_start, env->map.ceiling_color);
}

void	render_scene(t_env *env)
{
	reset_background(env);
	// TODO: Draw ceiling/floor
	render_all_rays(env, (int)(env->win_width / RES));
	draw_minimap(env);
}
