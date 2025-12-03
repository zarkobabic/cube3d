/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkau <eberkau@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 23:50:22 by zbabic            #+#    #+#             */
/*   Updated: 2025/12/03 01:18:29 by eberkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	find_first_horizontal_intersection(
	t_point_double *next_intersection, double ray_angle, const t_env *env,
		bool is_facing_down)
{
	t_point_double	p;
	int				tile_size;
	t_point_double	first_intersection;

	tile_size = env->map.tile_size;
	p = env->map.player.pos;
	if (is_facing_down)
		first_intersection.y = floor(p.y / tile_size) * tile_size + tile_size;
	else
		first_intersection.y = floor(p.y / tile_size) * tile_size - 0.000001;
	first_intersection.x = p.x + (first_intersection.y - p.y) / tan(ray_angle);
	*next_intersection = first_intersection;
}

static bool	check_horizontal_walls(t_point_double *horizontal_intersection,
		double ray_angle, const t_env *env, bool is_facing_down)
{
	t_point_double	next_intersection;
	int				tile_size;
	t_point_double	offset;
	t_point			check_point;

	tile_size = env->map.tile_size;
	find_first_horizontal_intersection(&next_intersection, ray_angle, env,
		is_facing_down);
	if (is_facing_down)
		offset.y = tile_size;
	else
		offset.y = -tile_size;
	offset.x = offset.y / tan(ray_angle);
	while (next_intersection.x < env->win_width && next_intersection.x >= 0
		&& next_intersection.y < env->win_height && next_intersection.y >= 0)
	{
		check_point.x = (int)next_intersection.x;
		check_point.y = (int)next_intersection.y;
		if (has_wall_at(env, &check_point))
			return (*horizontal_intersection = next_intersection, true);
		next_intersection.x += offset.x;
		next_intersection.y += offset.y;
	}
	return (false);
}

static void	find_first_vertical_intersection(t_point_double *next_intersection,
		double ray_angle, const t_env *env, bool is_facing_right)
{
	t_point_double	p;
	int				tile_size;
	t_point_double	first_intersection;

	tile_size = env->map.tile_size;
	p = env->map.player.pos;
	if (is_facing_right)
		first_intersection.x = floor(p.x / tile_size) * tile_size + tile_size;
	else
		first_intersection.x = floor(p.x / tile_size) * tile_size - 0.000001;
	first_intersection.y = p.y + (first_intersection.x - p.x) * tan(ray_angle);
	*next_intersection = first_intersection;
}

static bool	check_vertical_walls(t_point_double *vertical_intersection,
		double ray_angle, const t_env *env, bool is_facing_right)
{
	t_point_double	next_intersection;
	int				tile_size;
	t_point_double	offset;
	t_point			check_point;

	tile_size = env->map.tile_size;
	find_first_vertical_intersection(&next_intersection, ray_angle, env,
		is_facing_right);
	if (is_facing_right)
		offset.x = tile_size;
	else
		offset.x = -tile_size;
	offset.y = offset.x * tan(ray_angle);
	while (next_intersection.x < env->win_width && next_intersection.x >= 0
		&& next_intersection.y < env->win_height && next_intersection.y >= 0)
	{
		check_point.x = (int)next_intersection.x;
		check_point.y = (int)next_intersection.y;
		if (has_wall_at(env, &check_point))
			return (*vertical_intersection = next_intersection, true);
		next_intersection.x += offset.x;
		next_intersection.y += offset.y;
	}
	return (false);
}

double	get_distance_squared(const t_point_double *point,
		const t_point_double *player_pos)
{
	double	dx;
	double	dy;

	dx = point->x - player_pos->x;
	dy = point->y - player_pos->y;
	return (dx * dx + dy * dy);
}

static double	normalize_angle(double angle)
{
	while (angle < 0)
		angle += 2 * M_PI;
	while (angle >= 2 * M_PI)
		angle -= 2 * M_PI;
	return (angle);
}

static void	convert_to_point(t_point *dest, const t_point_double *src)
{
	dest->x = (int)src->x;
	dest->y = (int)src->y;
}

static int	get_wall_direction(double ray_angle, bool is_horizontal)
{
	if (is_horizontal)
	{
		if (ray_angle > 0 && ray_angle < M_PI)
			return (WALL_SOUTH);
		else
			return (WALL_NORTH);
	}
	else
	{
		if (ray_angle < M_PI / 2 || ray_angle > 3 * M_PI / 2)
			return (WALL_EAST);
		else
			return (WALL_WEST);
	}
}

static int	select_closest_wall(t_point *wall_collision_point,
	t_ray_hit *hit, const t_env *env, double ray_angle)
{
	double			h_dist;
	double			v_dist;

	if (hit->found[WALL_HOR] && hit->found[WALL_VER])
	{
		h_dist = get_distance_squared(&hit->intersections[WALL_HOR],
				&env->map.player.pos);
		v_dist = get_distance_squared(&hit->intersections[WALL_VER],
				&env->map.player.pos);
		if (h_dist < v_dist)
			return (convert_to_point(wall_collision_point, &hit->intersections[WALL_HOR]),
				get_wall_direction(ray_angle, true));
		else
			return (convert_to_point(wall_collision_point, &hit->intersections[WALL_VER]),
				get_wall_direction(ray_angle, false));
	}
	else if (hit->found[WALL_HOR])
		return (convert_to_point(wall_collision_point, &hit->intersections[WALL_HOR]),
			get_wall_direction(ray_angle, true));
	else if (hit->found[WALL_VER])
		return (convert_to_point(wall_collision_point, &hit->intersections[WALL_VER]),
			get_wall_direction(ray_angle, false));
	return (-1);
}

int	cast_ray(double ray_angle, t_point *wall_collision_point, const t_env *env)
{
	bool			directions[2];
	t_ray_hit		hit;

	ray_angle = normalize_angle(ray_angle);
	directions[ORIENT_SOUTH] = (ray_angle > 0 && ray_angle < M_PI);
	directions[ORIENT_EAST] = (ray_angle < M_PI / 2 || ray_angle > 3 * M_PI / 2);
	hit.found[WALL_HOR] = check_horizontal_walls(&hit.intersections[WALL_HOR],
			ray_angle, env, directions[ORIENT_SOUTH]);
	hit.found[WALL_VER] = check_vertical_walls(&hit.intersections[WALL_VER],
			ray_angle, env, directions[ORIENT_EAST]);
	return (select_closest_wall(wall_collision_point, &hit, env, ray_angle));
}
