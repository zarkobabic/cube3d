/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkau <eberkau@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 04:44:14 by eberkau           #+#    #+#             */
/*   Updated: 2025/12/06 04:49:29 by eberkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	normalize_angle(double angle)
{
	while (angle < 0)
		angle += 2 * M_PI;
	while (angle >= 2 * M_PI)
		angle -= 2 * M_PI;
	return (angle);
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

int	select_closest_wall(t_point *wall_collision_point,
	t_ray_hit *hit, const t_env *env, double ray_angle)
{
	double			h_dist;
	double			v_dist;

	if (hit->found[WALL_HOR] && hit->found[WALL_VER])
	{
		h_dist = get_distance_squared(&hit->at[WALL_HOR],
				&env->map.player.pos);
		v_dist = get_distance_squared(&hit->at[WALL_VER],
				&env->map.player.pos);
		if (h_dist < v_dist)
			return (convert_to_point(wall_collision_point, &hit->at[WALL_HOR]),
				get_wall_direction(ray_angle, true));
		else
			return (convert_to_point(wall_collision_point, &hit->at[WALL_VER]),
				get_wall_direction(ray_angle, false));
	}
	else if (hit->found[WALL_HOR])
		return (convert_to_point(wall_collision_point, &hit->at[WALL_HOR]),
			get_wall_direction(ray_angle, true));
	else if (hit->found[WALL_VER])
		return (convert_to_point(wall_collision_point, &hit->at[WALL_VER]),
			get_wall_direction(ray_angle, false));
	return (-1);
}
