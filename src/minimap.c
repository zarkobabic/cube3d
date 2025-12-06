/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkau <eberkau@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 11:48:42 by zbabic            #+#    #+#             */
/*   Updated: 2025/12/06 04:05:16 by eberkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	has_wall_at(const t_env *env, const t_point *point_in_pixel)
{
	int	tile_size;

	tile_size = env->map.tile_size;
	return (env->map.matrix[(int)floor(point_in_pixel->y
				/ tile_size)][(int)floor(point_in_pixel->x
			/ tile_size)] == MAP_WALL);
}

void	init_minimap(t_env *env)
{
	env->map.minimap_tile_size = (int)fmin(
		env->win_height * MINIMAP_RATIO / env->map.rows,
		env->win_width * MINIMAP_RATIO / env->map.cols);
	env->map.minimap_position_x = env->win_width - (env->map.cols
			* env->map.minimap_tile_size) - MINIMAP_MARGIN;
	env->map.minimap_position_y = MINIMAP_MARGIN;
}

void	draw_tile(const t_env *env, int x, int y)
{
	t_point	corner;

	corner.x = env->map.minimap_position_x + (x * env->map.minimap_tile_size);
	corner.y = env->map.minimap_position_y + (y * env->map.minimap_tile_size);
	if (env->map.matrix[y][x] == MAP_WALL)
		draw_square(env, env->map.minimap_tile_size - 1, &corner, COLOR_WALL);
	else if (env->map.matrix[y][x] == MAP_SPACE)
		draw_square(env, env->map.minimap_tile_size - 1, &corner, COLOR_SPACE);
	else
		draw_square(env, env->map.minimap_tile_size - 1, &corner, COLOR_EMPTY);
}

void	draw_minimap(const t_env *env)
{
	int				y;
	int				x;
	t_point_double	minimap_player_pos;

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
	minimap_player_pos.x = env->map.minimap_position_x
		+ (env->map.player.pos.x * env->map.minimap_tile_size
			/ env->map.tile_size);
	minimap_player_pos.y = env->map.minimap_position_y
		+ (env->map.player.pos.y * env->map.minimap_tile_size
			/ env->map.tile_size);
	draw_filled_circle(env, &minimap_player_pos, PLAYER_RADIUS, COLOR_PLAYER);
	render_all_rays_minimap(env, (int)(env->win_width / RES));
}
