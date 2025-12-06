/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 10:25:07 by zbabic            #+#    #+#             */
/*   Updated: 2025/12/06 15:58:24 by zbabic           ###   ########.fr       */
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

/// @brief Queries the primary monitor's screen dimensions.
/// MLX42's mlx_get_monitor_size() requires an initialized MLX context,
/// but there's no way to initialize without creating a window. As a workaround,
/// we use MLX_HEADLESS mode to create an invisible instance, fetch the
/// resolution, and immediately terminate it.
/// @param env
void	map_resize_screen(t_env *env)
{
	t_player	*player;
	int			screen_w;
	int			screen_h;
	mlx_t		*dummy_mlx;

	player = &env->map.player;
	mlx_set_setting(MLX_HEADLESS, true);
	dummy_mlx = mlx_init(1, 1, "Dummy", false);
	if (dummy_mlx)
	{
		mlx_get_monitor_size(0, &screen_w, &screen_h);
		if (env->win_width > screen_w)
			env->win_width = screen_w;
		if (env->win_height > screen_h)
			env->win_height = screen_h;
		mlx_terminate(dummy_mlx);
	}
	else
		error_exit(env, ERROR_MSG_MLX_INIT_FAIL, ERROR_CODE_MLX_ERROR);
	mlx_set_setting(MLX_HEADLESS, false);
	env->map.tile_size = (int)fmin(env->win_height / env->map.rows,
			env->win_width / env->map.cols);
	player->pos.y = (int)((player->pos.y + 0.5) * env->map.tile_size);
	player->pos.x = (int)((player->pos.x + 0.5) * env->map.tile_size);
}
