/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:05:15 by zbabic            #+#    #+#             */
/*   Updated: 2025/11/03 17:40:52 by zbabic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <stdio.h>

void	mlx_error_terminate(const char *msg, mlx_t *mlx, t_map *map)
{
	mlx_terminate(mlx);
	map_destructor(map);
	perror(msg);
	exit(1);
}

void	initialization_mlx(t_map *map)
{
	mlx_t		*mlx;
	mlx_image_t	*img;

	mlx = mlx_init(WIDTH, HEIGHT, "Cube3D", true);
	if (!mlx)
	{
		map_destructor(map);
		perror("MLX library init fail");
		exit(1);
	}
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img)
		mlx_error_terminate("MLX library failed to allocate memory", mlx, map);
	if (mlx_image_to_window(mlx, img, 0, 0) == -1)
		mlx_error_terminate("MLX library failed to create window", mlx, map);
	map->win = mlx;
	map->img = img;
	mlx_loop(mlx);
	mlx_terminate(mlx);
}
