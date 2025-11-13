/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:17:27 by zbabic            #+#    #+#             */
/*   Updated: 2025/11/11 18:06:04 by zbabic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	player_init(t_player *player)
{
	player->pos.x = -1;
	player->pos.y = -1;
	player->fov_rad = FOV * (M_PI / 180);
}

void	player_set_starting_orientation(t_player *player, char starting_orientation)
{
	if(starting_orientation == MAP_PLAYER_EAST)
		player->rot_angle = deg_to_rad(0);
	else if(starting_orientation == MAP_PLAYER_SOUTH)
		player->rot_angle = deg_to_rad(90);
	else if(starting_orientation == MAP_PLAYER_WEST)
		player->rot_angle = deg_to_rad(180);
	else
		player->rot_angle = deg_to_rad(270);
}
