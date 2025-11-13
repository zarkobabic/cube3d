/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 11:48:42 by zbabic            #+#    #+#             */
/*   Updated: 2025/11/11 18:04:50 by zbabic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

bool	has_wall_at(t_env *env, int pixel_x, int pixel_y)
{
	return (env->map.matrix[(int)floor(pixel_x)][(int)floor(pixel_y)]
		== MAP_WALL);
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
	if(env->map.matrix[y][x] == MAP_EMPTY)
		draw_square(env, env->map.tile_size - 1, &corner, COLOR_EMPTY);
	if (env->map.matrix[y][x] == MAP_WALL)
		draw_square(env, env->map.tile_size - 1, &corner, COLOR_WALL);
	else if (env->map.matrix[y][x] == MAP_SPACE)
		draw_square(env, env->map.tile_size - 1, &corner, COLOR_SPACE);
	else
	{
		draw_square(env, env->map.tile_size - 1, &corner, COLOR_EMPTY);
		draw_filled_circle(env, &env->map.player.pos, PLAYER_RADIUS, COLOR_PLAYER);
	}
}

void static draw_orientation_line(t_env *env)
{
	t_player	*player;
	t_point		ending;

	player = &env->map.player;
	ending.x = player->pos.x + cos(player->rot_angle) * 50;
	ending.y = player->pos.y + sin(player->rot_angle) * 50;
	draw_line(env, &player->pos, &ending, COLOR_PLAYER);
}

void	draw_minimap(t_env *env)
{
	int		y;
	int		x;

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
	draw_orientation_line(env);
}
