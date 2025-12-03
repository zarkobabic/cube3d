/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_rendering.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkau <eberkau@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 23:00:26 by zbabic            #+#    #+#             */
/*   Updated: 2025/12/03 19:47:58 by eberkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	render_ray_on_minimap(const t_env *env, const t_point *wall_collision_point)
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

void	render_wall_projection_for_ray(const t_env *env,
		const t_point *wall_collision_p, const t_ray_render_params *params)
{
	double				projected_wall_height;
	t_point				wall_start;
	t_point				wall_end;
	t_ray_tex_data		tex_data;
	t_point_double		temp_double;

	temp_double.x = wall_collision_p->x;
	temp_double.y = wall_collision_p->y;
	projected_wall_height = (env->map.tile_size /
				(sqrt(get_distance_squared(&temp_double, &env->map.player.pos))
					* cos(params->ray_angle - env->map.player.rot_angle)))
			* env->win_width / (2 * tan(env->map.player.fov_rad / 2));
	wall_start.y = (int)(env->win_height / 2 - projected_wall_height / 2);
	wall_start.x = params->column;
	wall_end.y = (int)(env->win_height / 2 + projected_wall_height / 2);
	wall_end.x = params->column;
	tex_data.wall_pos = wall_collision_p;
	tex_data.wall_start = &wall_start;
	tex_data.wall_end = &wall_end;
	tex_data.proj_height = projected_wall_height;
	tex_data.wall_dir = params->wall_dir;
	tex_data.tile_size = env->map.tile_size;
	draw_texture(env, &tex_data);
	render_floor(env, &wall_end);
	render_ceiling(env, &wall_start);
}
// draw_line(env, &wall_start, &wall_end, COLOR_PLAYER);
// -> For drawing a colored wall without texture -> switch with draw_texture()

void	render_all_rays_minimap(const t_env *env, int num_rays)
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

void	render_all_rays(const t_env *env, int num_rays)
{
	double				initial_angle;
	double				increment;
	int					i;
	t_point				wall_collision_point;
	t_ray_render_params	params;

	i = 0;
	increment = env->map.player.fov_rad / (num_rays - 1);
	initial_angle = env->map.player.rot_angle - env->map.player.fov_rad * 0.5;
	while (i < num_rays)
	{
		params.ray_angle = initial_angle;
		params.column = i;
		params.wall_dir = cast_ray(initial_angle, &wall_collision_point, env);
		// render_ray_on_minimap(env, &wall_collision_point);
		render_wall_projection_for_ray(env, &wall_collision_point, &params);
		initial_angle += increment;
		++i;
	}
}
