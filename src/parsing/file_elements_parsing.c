/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_elements_parsing.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkau <eberkau@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 21:16:44 by zbabic            #+#    #+#             */
/*   Updated: 2025/11/19 18:02:51 by eberkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "error.h"

static bool	file_check_valid_color_element(char *line, char *color_type,
		bool current_color_set, t_env *env)
{
	if (ft_strncmp(line, color_type, 2) == 0)
	{
		if (current_color_set)
		{
			free(line);
			if (ft_strncmp(color_type, MAP_FLOOR_COLOR, 2) == 0)
				error_exit(env, ERROR_MSG_MULTIPLE_DEFINITION_FLOOR_COLOR,
					ERROR_CODE_FILE_SYSTEM_ERROR);
			else
				error_exit(env, ERROR_MSG_MULTIPLE_DEFINITION_CEILING_COLOR,
					ERROR_CODE_FILE_SYSTEM_ERROR);
		}
		return (true);
	}
	return (false);
}

static bool	file_check_valid_texture_element(char *line, char *texture_type,
		char *texture_curr_path, t_env *env)
{
	if (ft_strncmp(line, texture_type, 3) == 0)
	{
		if (texture_curr_path)
		{
			free(line);
			if (ft_strncmp(texture_type, MAP_NORTH_TEXTURE, 3) == 0)
				error_exit(env, ERROR_MSG_MULTIPLE_DEFINITION_NO_TEXTURE,
					ERROR_CODE_FILE_SYSTEM_ERROR);
			else if (ft_strncmp(texture_type, MAP_SOUTH_TEXTURE, 3) == 0)
				error_exit(env, ERROR_MSG_MULTIPLE_DEFINITION_SO_TEXTURE,
					ERROR_CODE_FILE_SYSTEM_ERROR);
			else if (ft_strncmp(texture_type, MAP_EAST_TEXTURE, 3) == 0)
				error_exit(env, ERROR_MSG_MULTIPLE_DEFINITION_EA_TEXTURE,
					ERROR_CODE_FILE_SYSTEM_ERROR);
			else
				error_exit(env, ERROR_MSG_MULTIPLE_DEFINITION_WE_TEXTURE,
					ERROR_CODE_FILE_SYSTEM_ERROR);
		}
		return (true);
	}
	return (false);
}

void	file_parse_one_element(char *line, t_env *env)
{
	while (is_whitespace(*line))
		line++;
	if (file_check_valid_texture_element(line, MAP_NORTH_TEXTURE,
			env->map.no_texture, env))
		return (parse_texture(line + 3, &env->map.no_texture, env));
	else if (file_check_valid_texture_element(line, MAP_SOUTH_TEXTURE,
			env->map.so_texture, env))
		return (parse_texture(line + 3, &env->map.so_texture, env));
	else if (file_check_valid_texture_element(line, MAP_EAST_TEXTURE,
			env->map.ea_texture, env))
		return (parse_texture(line + 3, &env->map.ea_texture, env));
	else if (file_check_valid_texture_element(line, MAP_WEST_TEXTURE,
			env->map.we_texture, env))
		return (parse_texture(line + 3, &env->map.we_texture, env));
	else if (file_check_valid_color_element(line, MAP_FLOOR_COLOR,
			env->map.floor_color, env))
		return (parse_rgb(line + 2, &env->map.floor_color,
			&env->map.floor_color_set, env));
	else if (file_check_valid_color_element(line, MAP_CEILING_COLOR,
			env->map.ceiling_color, env))
		return (parse_rgb(line + 2, &env->map.ceiling_color,
			&env->map.ceiling_color_set, env));
	free(line);
	error_exit(env, ERROR_MSG_UNEXPECTED_FILE_LINE,
		ERROR_CODE_FILE_SYSTEM_ERROR);
}

void	file_check_all_elements_parsed(char *line, t_env *env)
{
	if (!env->map.no_texture)
		return (free(line), error_exit(env, ERROR_MSG_MISSING_NO_TEXTURE,
				ERROR_CODE_FILE_SYSTEM_ERROR));
	if (!env->map.so_texture)
		return (free(line), error_exit(env, ERROR_MSG_MISSING_SO_TEXTURE,
				ERROR_CODE_FILE_SYSTEM_ERROR));
	if (!env->map.we_texture)
		return (free(line), error_exit(env, ERROR_MSG_MISSING_WE_TEXTURE,
				ERROR_CODE_FILE_SYSTEM_ERROR));
	if (!env->map.ea_texture)
		return (free(line), error_exit(env, ERROR_MSG_MISSING_EA_TEXTURE,
				ERROR_CODE_FILE_SYSTEM_ERROR));
	if (!env->map.ceiling_color_set)
		return (free(line), error_exit(env, ERROR_MSG_MISSING_CEILING_COLOR,
				ERROR_CODE_FILE_SYSTEM_ERROR));
	if (!env->map.floor_color_set)
		return (free(line), error_exit(env, ERROR_MSG_MISSING_FLOOR_COLOR,
				ERROR_CODE_FILE_SYSTEM_ERROR));
}
