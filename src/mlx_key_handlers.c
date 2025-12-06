/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_key_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkau <eberkau@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 00:21:31 by zbabic            #+#    #+#             */
/*   Updated: 2025/12/06 04:32:03 by eberkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	forward_backward_handler(mlx_key_data_t *keydata, t_env *env)
{
	if (keydata->key == MLX_KEY_W)
	{
		if (keydata->action == MLX_PRESS)
			env->map.player.keys.w_pressed = 1;
		else if (keydata->action == MLX_RELEASE)
			env->map.player.keys.w_pressed = 0;
	}
	else if (keydata->key == MLX_KEY_S)
	{
		if (keydata->action == MLX_PRESS)
			env->map.player.keys.s_pressed = 1;
		else if (keydata->action == MLX_RELEASE)
			env->map.player.keys.s_pressed = 0;
	}
	else if (keydata->key == MLX_KEY_LEFT_SHIFT)
	{
		if (keydata->action == MLX_PRESS)
			env->map.player.keys.lshift = 1;
		else if (keydata->action == MLX_RELEASE)
			env->map.player.keys.lshift = 0;
	}
}

static void	sideways_handler(mlx_key_data_t *keydata, t_env *env)
{
	if (keydata->key == MLX_KEY_A)
	{
		if (keydata->action == MLX_PRESS)
			env->map.player.keys.a_pressed = 1;
		else if (keydata->action == MLX_RELEASE)
			env->map.player.keys.a_pressed = 0;
	}
	else
	{
		if (keydata->action == MLX_PRESS)
			env->map.player.keys.d_pressed = 1;
		else if (keydata->action == MLX_RELEASE)
			env->map.player.keys.d_pressed = 0;
	}
}

static void	camera_buttons_handler(mlx_key_data_t *keydata, t_env *env)
{
	if (keydata->key == MLX_KEY_LEFT)
	{
		if (keydata->action == MLX_PRESS)
			env->map.player.keys.left_arrow = 1;
		else if (keydata->action == MLX_RELEASE)
			env->map.player.keys.left_arrow = 0;
	}
	else
	{
		if (keydata->action == MLX_PRESS)
			env->map.player.keys.right_arrow = 1;
		else if (keydata->action == MLX_RELEASE)
			env->map.player.keys.right_arrow = 0;
	}
}

void	key_handler(mlx_key_data_t keydata, void *param)
{
	t_env	*env;

	env = (t_env *)param;
	if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_S
		|| keydata.key == MLX_KEY_LEFT_SHIFT)
		forward_backward_handler(&keydata, env);
	else if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_D)
		sideways_handler(&keydata, env);
	else if (keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_RIGHT)
		camera_buttons_handler(&keydata, env);
	else if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(env->win);
}
