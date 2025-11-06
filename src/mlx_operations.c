/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:05:15 by zbabic            #+#    #+#             */
/*   Updated: 2025/11/05 19:54:06 by zbabic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "error.h"

void	mlx_initialization(t_env *env)
{
	mlx_t		*mlx;
	mlx_image_t	*img;

	mlx = mlx_init(env->win_width, env->win_height, "Cube3D", true);
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
	mlx_loop(mlx);
	mlx_terminate(mlx);
	env->win = NULL;
}
