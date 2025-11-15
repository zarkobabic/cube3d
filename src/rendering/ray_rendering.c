/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_rendering.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 23:00:26 by zbabic            #+#    #+#             */
/*   Updated: 2025/11/16 00:15:58 by zbabic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	render_ray_on_minimap(t_env *env, t_point *wall_collision_point)
{
	t_point	minimap_starting;
	t_point	minimap_collision;

	minimap_starting.x = env->map.minimap_position_x + (env->map.player.pos.x
			* MINIMAP_RATIO);
	minimap_starting.y = env->map.minimap_position_y + (env->map.player.pos.y
			* MINIMAP_RATIO);
	minimap_collision.x = env->map.minimap_position_x + (wall_collision_point->x
			* MINIMAP_RATIO);
	minimap_collision.y = env->map.minimap_position_y + (wall_collision_point->y
			* MINIMAP_RATIO);
	draw_line(env, &minimap_starting, &minimap_collision, COLOR_PLAYER);
}

void	render_wall_projectin_for_ray(t_env *env, double ray_angle,
		t_point *wall_collision_p, int i)
{
	double			wall_distance;
	t_point_double	wall_collision_point;
	double			projected_wall_height;
	t_point			wall_start;
	t_point			wall_end;

	wall_collision_point.x = wall_collision_p->x;
	wall_collision_point.y = wall_collision_p->y;
	wall_distance = sqrt(get_distance_squared(&wall_collision_point,
				&env->map.player.pos)) * cos(ray_angle
			- env->map.player.rot_angle);
	projected_wall_height = (WALL_HEIGHT / wall_distance) * env->win_width / (2
			* tan(env->map.player.fov_rad / 2));
	wall_start.y = (int)(env->win_height / 2 - projected_wall_height / 2);
	wall_start.x = i;
	wall_end.y = (int)(env->win_height / 2 + projected_wall_height / 2);
	wall_end.x = i;
	if (wall_start.y < 0)
		wall_start.y = 0;
	if (wall_end.y >= env->win_height)
		wall_end.y = env->win_height - 1;
	draw_line(env, &wall_start, &wall_end, COLOR_PLAYER);
}

void	render_all_rays_minimap(t_env *env, int num_rays)
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
		render_ray_on_minimap(env, &wall_collision_point);
		initial_angle += increment;
		++i;
	}
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
		// render_ray_on_minimap(env, &wall_collision_point);
		render_wall_projectin_for_ray(env, initial_angle, &wall_collision_point,
			i);
		initial_angle += increment;
		++i;
	}
}
