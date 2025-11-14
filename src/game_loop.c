/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 23:46:09 by zbabic            #+#    #+#             */
/*   Updated: 2025/11/14 02:07:18 by zbabic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	rotate_camera_if_necessary(t_player *player, bool *scene_changed)
{
	int	rot_dir;

	rot_dir = player->keys.right_arrow - player->keys.left_arrow;
	if (rot_dir != 0)
	{
		player->rot_angle += rot_dir * player->rot_speed;
		if (player->rot_angle < 0)
			player->rot_angle += 2 * M_PI;
		else if (player->rot_angle >= 2 * M_PI)
			player->rot_angle -= 2 * M_PI;
		*scene_changed = true;
	}
}

void	move_player_if_necessary(t_player *player, bool *scene_changed)
{
	int		forward;
	int		sideways;
	double	dx;
	double	dy;
	double	length;

	forward = player->keys.w_pressed - player->keys.s_pressed;
	sideways = player->keys.d_pressed - player->keys.a_pressed;
	if (forward != 0 || sideways != 0)
	{
		dx = forward * cos(player->rot_angle) - sideways
			* sin(player->rot_angle);
		dy = forward * sin(player->rot_angle) + sideways
			* cos(player->rot_angle);
		length = sqrt(dx * dx + dy * dy);
		if (length > 0)
		{
			dx = (dx / length) * player->move_speed;
			dy = (dy / length) * player->move_speed;
		}
		player->pos.x += dx;
		player->pos.y += dy;
		*scene_changed = true;
	}
}

void	game_loop(void *param)
{
	t_player	*player;
	bool		scene_changed;

	player = &((t_env *)param)->map.player;
	scene_changed = false;
	rotate_camera_if_necessary(player, &scene_changed);
	move_player_if_necessary(player, &scene_changed);
	if (scene_changed)
		render_scene((t_env *)param);
}
