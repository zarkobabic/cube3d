/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 23:46:09 by zbabic            #+#    #+#             */
/*   Updated: 2025/12/06 15:38:13 by zbabic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	rotate_camera_if_necessary(t_player *player, bool *scene_changed,
		const t_env *env)
{
	int	rot_dir;

	rot_dir = player->keys.right_arrow - player->keys.left_arrow;
	if (rot_dir != 0)
	{
		player->rot_angle += rot_dir * player->rot_speed * env->win->delta_time;
		if (player->rot_angle < 0)
			player->rot_angle += 2 * M_PI;
		else if (player->rot_angle >= 2 * M_PI)
			player->rot_angle -= 2 * M_PI;
		*scene_changed = true;
	}
}

static void	handle_collisions(const t_env *env, double *dx, double *dy)
{
	t_player	*player;
	char		**map;
	int			tile_size;

	player = (t_player *)&env->map.player;
	map = env->map.matrix;
	tile_size = env->map.tile_size;
	if (map[(int)(player->pos.y / tile_size)][(int)((player->pos.x + *dx)
			/ tile_size)] == MAP_WALL)
		*dx = 0;
	if (map[(int)((player->pos.y + *dy) / tile_size)][(int)(player->pos.x
			/ tile_size)] == MAP_WALL)
		*dy = 0;
}

static void	handle_sprint(int forward, int shift_pressed, double *dx,
		double *dy)
{
	if (forward > 0 && shift_pressed)
	{
		*dx *= 2;
		*dy *= 2;
	}
}

static void	move_player_if_necessary(t_player *player, bool *scene_changed,
		const t_env *env)
{
	int		forward;
	int		sideways;
	double	dx;
	double	dy;
	double	length;

	forward = player->keys.w_pressed - player->keys.s_pressed;
	sideways = player->keys.d_pressed - player->keys.a_pressed;
	if (forward == 0 && sideways == 0)
		return ;
	dx = forward * cos(player->rot_angle) - sideways * sin(player->rot_angle);
	dy = forward * sin(player->rot_angle) + sideways * cos(player->rot_angle);
	length = sqrt(dx * dx + dy * dy);
	if (length > 0)
	{
		dx = (dx / length) * player->move_speed * env->map.tile_size
			* env->win->delta_time;
		dy = (dy / length) * player->move_speed * env->map.tile_size
			* env->win->delta_time;
	}
	handle_sprint(forward, player->keys.lshift, &dx, &dy);
	handle_collisions(env, &dx, &dy);
	player->pos.x += dx;
	player->pos.y += dy;
	*scene_changed = true;
}

void	game_loop(void *param)
{
	t_player	*player;
	bool		scene_changed;

	player = &((t_env *)param)->map.player;
	scene_changed = false;
	rotate_camera_if_necessary(player, &scene_changed, (t_env *)param);
	move_player_if_necessary(player, &scene_changed, (t_env *)param);
	if (scene_changed)
		render_scene((t_env *)param);
}
