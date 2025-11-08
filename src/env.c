/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:23:58 by zbabic            #+#    #+#             */
/*   Updated: 2025/11/07 21:25:24 by zbabic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	env_destroy(t_env *env)
{
	if (env->win)
		mlx_terminate(env->win);
	map_destroy(&env->map);
}

void	env_init(t_env *env)
{
	env->img = NULL;
	env->win = NULL;
	env->win_width = WINDOW_WIDTH;
	env->win_height = WINDOW_HEIGHT;
	map_init(env);
}
