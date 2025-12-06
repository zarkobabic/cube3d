/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkau <eberkau@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 10:25:07 by zbabic            #+#    #+#             */
/*   Updated: 2025/12/06 05:01:52 by eberkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
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
	if (map->textures.no.path)
		free(map->textures.no.path);
	if (map->textures.so.path)
		free(map->textures.so.path);
	if (map->textures.we.path)
		free(map->textures.we.path);
	if (map->textures.ea.path)
		free(map->textures.ea.path);
	if (map->textures.no.mlx_tex)
		mlx_delete_texture(map->textures.no.mlx_tex);
	if (map->textures.so.mlx_tex)
		mlx_delete_texture(map->textures.so.mlx_tex);
	if (map->textures.we.mlx_tex)
		mlx_delete_texture(map->textures.we.mlx_tex);
	if (map->textures.ea.mlx_tex)
		mlx_delete_texture(map->textures.ea.mlx_tex);
	if (map->matrix)
		matrix_destroy(&map->matrix, map->rows);
}

void	map_init(t_env *env)
{
	t_map	*map;

	map = &env->map;
	map->textures.no.path = NULL;
	map->textures.no.mlx_tex = NULL;
	map->textures.so.path = NULL;
	map->textures.so.mlx_tex = NULL;
	map->textures.we.path = NULL;
	map->textures.we.mlx_tex = NULL;
	map->textures.ea.path = NULL;
	map->textures.ea.mlx_tex = NULL;
	map->matrix = NULL;
	map->rows = -1;
	map->cols = -1;
	map->floor_color = 0;
	map->floor_color_set = false;
	map->ceiling_color = 0;
	map->ceiling_color_set = false;
	map->map_file_fd = -1;
	map->tile_size = TILE_SIZE;
	player_init(&map->player);
}

void	map_resize_screen(t_env *env)
{
	t_player	*player;

	player = &env->map.player;
	env->map.tile_size = (int)fmin(env->win_height / env->map.rows,
			env->win_width / env->map.cols);
	player->pos.y = (int)((player->pos.y + 0.5) * env->map.tile_size);
	player->pos.x = (int)((player->pos.x + 0.5) * env->map.tile_size);
	player->move_speed = player->move_speed * env->map.tile_size / TILE_SIZE;
}

// TODO: just for testing delete after
void	test_map_print(t_env *env)
{
	int	i;
	int	j;

	printf("MAP INFO \n");
	printf("map_file_fd: %d|\n", env->map.map_file_fd);
	printf("rows: %d|\n", env->map.rows);
	printf("cols: %d|\n", env->map.cols);
	// printf("tile_size: %d|\n", env->map.tile_size); // TODO: delete or uncomment?
	printf("no_texture: %s|\n", env->map.textures.no.path);
	printf("so_texture: %s|\n", env->map.textures.so.path);
	printf("we_texture: %s|\n", env->map.textures.we.path);
	printf("ea_texture: %s|\n", env->map.textures.ea.path);
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
