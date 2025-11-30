/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_loading.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkau <eberkau@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 17:53:14 by eberkau           #+#    #+#             */
/*   Updated: 2025/11/30 18:53:06 by eberkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "error.h"

static void	load_single_texture(t_env *env, t_texture *texture)
{
	if (!env || !texture)
		return ;
	file_check_extension(env, texture->path, ".png",
		ERROR_MSG_WRONG_TEX_FILE_EXTENSION);
	texture->mlx_tex = mlx_load_png(texture->path);
	if (!texture->mlx_tex)
		error_exit(env, ERROR_MSG_MLX_TEXTURE_LOAD_FAIL, ERROR_CODE_MLX_ERROR);
}

void	load_textures(t_env *env)
{
	if (!env)
		return ;
	load_single_texture(env, &(env->map.textures.no));
	load_single_texture(env, &(env->map.textures.so));
	load_single_texture(env, &(env->map.textures.we));
	load_single_texture(env, &(env->map.textures.ea));
}
