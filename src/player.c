/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:17:27 by zbabic            #+#    #+#             */
/*   Updated: 2025/11/11 13:52:15 by zbabic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	player_init(t_player *player)
{
	player->pos.x = -1;
	player->pos.y = -1;
	player->player_dir = '\0';
	player->fov_rad = FOV * (M_PI / 180);
}
