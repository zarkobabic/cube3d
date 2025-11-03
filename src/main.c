/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:15:43 by zbabic            #+#    #+#             */
/*   Updated: 2025/11/03 17:24:15 by zbabic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	map_destructor(t_map *map)
{
	(void)map;
}

int main()
{
	t_map	map;

	initialization_mlx(&map);
	map_destructor(&map);
	return 0;
}