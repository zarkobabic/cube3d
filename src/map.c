/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 10:25:07 by zbabic            #+#    #+#             */
/*   Updated: 2025/11/07 21:34:55 by zbabic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "error.h"
#include <unistd.h>

// static void	matrix_destroy(char ***matrix, int rows)
// {
// 	int i;

// 	if(!matrix || !*matrix)
// 		return ;
// 	i = 0;
// 	while(i < rows)
// 	{
// 		if((*matrix)[i])
// 			free((*matrix)[i]);
// 		++i;
// 	}
// 	free(*matrix);
// 	*matrix = NULL;
// }

// static char	**create_matrix(int rows, int cols)
// {
// 	char	**matrix;
// 	int		i;

// 	i = 0;
// 	matrix = (char **)malloc(rows * sizeof(char *));
// 	if (!matrix)
// 		return (NULL);
// 	while (i < rows)
// 	{
// 		matrix[i] = (char *)malloc(cols * sizeof(char));
// 		if (!matrix[i])
// 			return (matrix_destroy(&matrix, i), NULL);
// 		++i;
// 	}
// 	return (matrix);
// }

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
	// if(map->matrix)
	// 	matrix_destroy(&map->matrix, map->rows);
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
