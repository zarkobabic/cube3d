/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_rendering.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkau <eberkau@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 00:03:10 by zbabic            #+#    #+#             */
/*   Updated: 2025/12/03 00:50:32 by eberkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	reset_background(const t_env *env)
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


void	render_floor(const t_env *env, t_point *wall_end)
{
	t_point	screen_bottom_edge;

	if (wall_end->y >= env->win_height)
		wall_end->y = env->win_height - 1;
	screen_bottom_edge.y = env->win_height;
	screen_bottom_edge.x = wall_end->x;
	draw_line(env, wall_end, &screen_bottom_edge, env->map.floor_color);
}

void	render_ceiling(const t_env *env, t_point *wall_start)
{
	t_point	screen_top_edge;

	if (wall_start->y < 0)
		wall_start->y = 0;
	screen_top_edge.y = 0;
	screen_top_edge.x = wall_start->x;
	draw_line(env, &screen_top_edge, wall_start, env->map.ceiling_color);
}

void	render_scene(const t_env *env)
{
	reset_background(env);
	render_all_rays(env, (int)(env->win_width / RES));
	draw_minimap(env);
}
