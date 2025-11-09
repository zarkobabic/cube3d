/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 10:25:07 by zbabic            #+#    #+#             */
/*   Updated: 2025/11/09 15:48:29 by zbabic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "error.h"
#include <unistd.h>

static void	matrix_destroy(char ***matrix, int rows)
{
	int	i;

	if (!matrix || !*matrix)
		return ;
	i = 0;
	while (i < rows)
	{
		if ((*matrix)[i])
			free((*matrix)[i]);
		++i;
	}
	free(*matrix);
	*matrix = NULL;
}

void	map_destroy(t_map *map)
{
	if (map->map_file_fd != -1)
		close(map->map_file_fd);
	if (map->no_texture)
		free(map->no_texture);
	if (map->so_texture)
		free(map->so_texture);
	if (map->we_texture)
		free(map->we_texture);
	if (map->ea_texture)
		free(map->ea_texture);
	if (map->matrix)
		matrix_destroy(&map->matrix, map->rows);
}

void	map_init(t_env *env)
{
	t_map	*map;

	map = &env->map;
	map->no_texture = NULL;
	map->so_texture = NULL;
	map->we_texture = NULL;
	map->ea_texture = NULL;
	map->matrix = NULL;
	map->rows = -1;
	map->cols = -1;
	map->floor_color = -1;
	map->ceiling_color = -1;
	map->map_file_fd = -1;
	player_init(&map->player);
}

void	test_map_print(t_env *env)
{
	int	i;
	int	j;

	printf("MAP INFO \n");
	printf("map_file_fd: %d|\n", env->map.map_file_fd);
	printf("rows: %d|\n", env->map.rows);
	printf("cols: %d|\n", env->map.cols);
	//printf("tile_size: %d|\n", env->map.tile_size);
	printf("no_texture: %s|\n", env->map.no_texture);
	printf("so_texture: %s|\n", env->map.so_texture);
	printf("we_texture: %s|\n", env->map.we_texture);
	printf("ea_texture: %s|\n", env->map.ea_texture);
	printf("floor_color: %d|\n", env->map.floor_color);
	printf("ceiling_color: %d|\n", env->map.ceiling_color);
	i = 0;
	while (i < env->map.rows)
	{
		j = 0;
		printf("|");
		while (j < env->map.cols)
			printf("%c", env->map.matrix[i][j++]);
		printf("|\n");
		++i;
	}
}
