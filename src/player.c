/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkau <eberkau@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:17:27 by zbabic            #+#    #+#             */
/*   Updated: 2025/11/19 18:12:46 by eberkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_init(t_player *player)
{
	player->pos.x = -1;
	player->pos.y = -1;
	player->fov_rad = FOV * (M_PI / 180);
	player->move_speed = MOVE_SPEED;
	player->rot_speed = ROTATION_SPEED;
	ft_bzero(&player->keys, sizeof(t_keys));
}

void	player_set_starting_orientation(t_player *player,
		char starting_orientation)
{
	if (starting_orientation == MAP_PLAYER_EAST)
		player->rot_angle = deg_to_rad(0);
	else if (starting_orientation == MAP_PLAYER_SOUTH)
		player->rot_angle = deg_to_rad(90);
	else if (starting_orientation == MAP_PLAYER_WEST)
		player->rot_angle = deg_to_rad(180);
	else
		player->rot_angle = deg_to_rad(270);
}
