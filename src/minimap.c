/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 11:48:42 by zbabic            #+#    #+#             */
/*   Updated: 2025/11/15 02:09:42 by zbabic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

bool	has_wall_at(t_env *env, t_point *point_in_pixel)
{
	int	tile_size;

	tile_size = env->map.tile_size;
	return (env->map.matrix[(int)floor(point_in_pixel->y
				/ tile_size)][(int)floor(point_in_pixel->x
			/ tile_size)] == MAP_WALL);
}

void	init_minimap(t_env *env)
{
	env->win_width = TILE_SIZE * env->map.cols;
	env->win_height = TILE_SIZE * env->map.rows;
}

void	draw_tile(t_env *env, int x, int y)
{
	t_point	corner;

	corner.x = x * env->map.tile_size;
	corner.y = y * env->map.tile_size;
	if (env->map.matrix[y][x] == MAP_WALL)
		draw_square(env, env->map.tile_size - 1, &corner, COLOR_WALL);
	else if (env->map.matrix[y][x] == MAP_SPACE)
		draw_square(env, env->map.tile_size - 1, &corner, COLOR_SPACE);
	else
		draw_square(env, env->map.tile_size - 1, &corner, COLOR_EMPTY);
}

// void static	draw_orientation_line(t_env *env)
// {
// 	t_player	*player;
// 	t_point		starting;
// 	t_point		ending;

// 	player = &env->map.player;
// 	starting.x = (int)player->pos.x;
// 	starting.y = (int)player->pos.y;
// 	ending.x = player->pos.x + cos(player->rot_angle) * 50;
// 	ending.y = player->pos.y + sin(player->rot_angle) * 50;
// 	draw_line(env, &starting, &ending, COLOR_PLAYER);
// }

void	draw_minimap(t_env *env)
{
	int	y;
	int	x;

	y = 0;
	while (y < env->map.rows)
	{
		x = 0;
		while (x < env->map.cols)
		{
			draw_tile(env, x, y);
			++x;
		}
		++y;
	}
	draw_filled_circle(env, &env->map.player.pos, PLAYER_RADIUS, COLOR_PLAYER);
	// draw_orientation_line(env);
}
