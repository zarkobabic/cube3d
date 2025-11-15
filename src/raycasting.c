/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 23:50:22 by zbabic            #+#    #+#             */
/*   Updated: 2025/11/15 18:12:51 by zbabic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	find_first_horizontal_intersection(
	t_point_double *next_intersection, double ray_angle, t_env *env,
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
		first_intersection.y = floor(p.y / tile_size) * tile_size - 1;
	first_intersection.x = p.x + (first_intersection.y - p.y) / tan(ray_angle);
	*next_intersection = first_intersection;
}

static bool	check_horizontal_walls(t_point_double *horizontal_intersection,
		double ray_angle, t_env *env, bool is_facing_down)
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
		double ray_angle, t_env *env, bool is_facing_right)
{
	t_point_double	p;
	int				tile_size;
	t_point_double	first_intersection;

	tile_size = env->map.tile_size;
	p = env->map.player.pos;
	if (is_facing_right)
		first_intersection.x = floor(p.x / tile_size) * tile_size + tile_size;
	else
		first_intersection.x = floor(p.x / tile_size) * tile_size - 1;
	first_intersection.y = p.y + (first_intersection.x - p.x) * tan(ray_angle);
	*next_intersection = first_intersection;
}

static bool	check_vertical_walls(t_point_double *vertical_intersection,
		double ray_angle, t_env *env, bool is_facing_right)
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

double	get_distance_squared(t_point_double *point,
		t_point_double *player_pos)
{
	double	dx;
	double	dy;

	dx = point->x - player_pos->x;
	dy = point->y - player_pos->y;
	return (dx * dx + dy * dy);
}

static void	get_closest_intersection(t_point_double *result,
		t_point_double *horizontal, t_point_double *vertical,
		t_point_double *player_pos)
{
	double	h_dist;
	double	v_dist;

	h_dist = get_distance_squared(horizontal, player_pos);
	v_dist = get_distance_squared(vertical, player_pos);
	if (h_dist < v_dist)
		*result = *horizontal;
	else
		*result = *vertical;
}

static double	normalize_angle(double angle)
{
	while (angle < 0)
		angle += 2 * M_PI;
	while (angle >= 2 * M_PI)
		angle -= 2 * M_PI;
	return (angle);
}

static void	convert_to_point(t_point *dest, t_point_double *src)
{
	dest->x = (int)src->x;
	dest->y = (int)src->y;
}

static void	select_closest_wall(t_point *wall_collision_point,
	t_point_double *intersections, bool *found, t_env *env)
{
	t_point_double	result;

	if (found[0] && found[1])
	{
		get_closest_intersection(&result, &intersections[0],
			&intersections[1], &env->map.player.pos);
		convert_to_point(wall_collision_point, &result);
	}
	else if (found[0])
		convert_to_point(wall_collision_point, &intersections[0]);
	else if (found[1])
		convert_to_point(wall_collision_point, &intersections[1]);
}

void	cast_ray(double ray_angle, t_point *wall_collision_point, t_env *env)
{
	bool			directions[2];
	bool			found[2];
	t_point_double	intersections[2];

	ray_angle = normalize_angle(ray_angle);
	directions[0] = (ray_angle > 0 && ray_angle < M_PI);
	directions[1] = (ray_angle < M_PI / 2 || ray_angle > 3 * M_PI / 2);
	found[0] = check_horizontal_walls(&intersections[0],
			ray_angle, env, directions[0]);
	found[1] = check_vertical_walls(&intersections[1],
			ray_angle, env, directions[1]);
	select_closest_wall(wall_collision_point, intersections, found, env);
}
