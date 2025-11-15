/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_rendering.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 23:00:26 by zbabic            #+#    #+#             */
/*   Updated: 2025/11/15 02:12:41 by zbabic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	render_ray(t_env *env, t_point *wall_collision_point)
{
	t_point	starting;

	starting.x = (int)env->map.player.pos.x;
	starting.y = (int)env->map.player.pos.y;
	draw_line(env, &starting, wall_collision_point, COLOR_PLAYER);
}

void	render_all_rays(t_env *env, int num_rays)
{
	double	initial_angle;
	double	increment;
	int		i;
	t_point	wall_collision_point;

	i = 0;
	increment = env->map.player.fov_rad / (num_rays - 1);
	initial_angle = env->map.player.rot_angle - env->map.player.fov_rad * 0.5;
	while (i < num_rays)
	{
		cast_ray(initial_angle, &wall_collision_point, env);
		render_ray(env, &wall_collision_point);
		initial_angle += increment;
		++i;
	}
}
