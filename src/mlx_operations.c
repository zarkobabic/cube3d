/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkau <eberkau@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:05:15 by zbabic            #+#    #+#             */
/*   Updated: 2025/12/06 05:27:13 by eberkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "error.h"

static void	mlx_register_hooks(t_env *env)
{
	mlx_key_hook(env->win, key_handler, env);
	mlx_loop_hook(env->win, game_loop, env);
}

void	mlx_initialization(t_env *env)
{
	mlx_t		*mlx;
	mlx_image_t	*img;

	mlx = mlx_init(env->win_width, env->win_height, "Cub3D", true);
	if (!mlx)
		error_exit(env, ERROR_MSG_MLX_INIT_FAIL, ERROR_CODE_MLX_ERROR);
	img = mlx_new_image(mlx, env->win_width, env->win_height);
	if (!img)
		error_exit(env, ERROR_MSG_MLX_MEMORY_ALLOCATION_FAILED,
			ERROR_CODE_MLX_ERROR);
	if (mlx_image_to_window(mlx, img, 0, 0) == -1)
		error_exit(env, ERROR_MSG_MLX_WINDOW_CREATION_FAILED,
			ERROR_CODE_MLX_ERROR);
	env->win = mlx;
	env->img = img;
	mlx_register_hooks(env);
}

void	mlx_destroy(t_env *env)
{
	mlx_terminate(env->win);
	env->win = NULL;
}
