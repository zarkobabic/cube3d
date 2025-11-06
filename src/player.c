/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:17:27 by zbabic            #+#    #+#             */
/*   Updated: 2025/11/04 16:18:56 by zbabic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	player_init(t_player *player)
{
	player->coordinates[0] = -1;
	player->coordinates[1] = -1;
	player->player_dir = '\0';
}
