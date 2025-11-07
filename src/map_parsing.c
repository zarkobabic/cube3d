/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:32:03 by zbabic            #+#    #+#             */
/*   Updated: 2025/11/07 20:36:38 by zbabic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "error.h"
#include <fcntl.h>
#include <unistd.h>

void	map_parse_check_file_extension(t_env *env, char *map_file_path)
{
	int		has_no_extension;
	size_t	len;

	len = ft_strlen(map_file_path);
	if (len < 4)
		error_exit(env, ERROR_MSG_WRONG_FILE_EXTENSION,
			ERROR_CODE_FILE_SYSTEM_ERROR);
	has_no_extension = ft_strncmp(&map_file_path[len - 4], ".pub", 5);
	if (has_no_extension)
		error_exit(env, ERROR_MSG_WRONG_FILE_EXTENSION,
			ERROR_CODE_FILE_SYSTEM_ERROR);
}

bool	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r')
		return (true);
	return (false);
}

bool	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!is_whitespace(line[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	map_check_valid_texture_element(char *line, char *texture_type,
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

bool	map_check_valid_color_element(char *line, char *color_type,
		int current_color, t_env *env)
{
	if (ft_strncmp(line, color_type, 2) == 0)
	{
		if (current_color != -1)
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

void	free_split(char ***split)
{
	int	i;

	if (!split || !(*split))
		return ;
	i = 0;
	while ((*split)[i])
	{
		free((*split)[i]);
		++i;
	}
	free(*split);
	*split = NULL;
}

void	parse_rgb(char *line, int *color_loc_to_fill, t_env *env)
{
	int		i;
	char	**split;
	int		rgb[3];

	split = ft_split(line, ',');
	if (!split)
		return (free(line - 2), error_exit(env, ERROR_MSG_COLOR_PARSING_FAILED,
				ERROR_CODE_FILE_SYSTEM_ERROR));
	i = 0;
	while (split[i])
		++i;
	if (i != 3)
		return (free(line - 2), free_split(&split), error_exit(env,
				ERROR_MSG_WRONG_COLOR_FORMAT, ERROR_CODE_FILE_SYSTEM_ERROR));
	rgb[COLOR_R] = ft_atoi(split[COLOR_R]);
	rgb[COLOR_G] = ft_atoi(split[COLOR_G]);
	rgb[COLOR_B] = ft_atoi(split[COLOR_B]);
	if (rgb[COLOR_R] < 0 || rgb[COLOR_R] > 255 || rgb[COLOR_G] < 0
		|| rgb[COLOR_G] > 255 || rgb[COLOR_B] < 0 || rgb[COLOR_B] > 255)
		free(line - 2), free_split(&split), error_exit(env,
			ERROR_MSG_WRONG_COLOR_COMPONENT_RANGE,
			ERROR_CODE_FILE_SYSTEM_ERROR);
	*color_loc_to_fill = (rgb[COLOR_R] << 16 | rgb[COLOR_G] << 8 | rgb[COLOR_B]);
	free_split(&split);
}

void	parse_texture(char *line, char **texture, t_env *env)
{
	int		i;
	char	*path;

	i = 0;
	while (line[i] && (is_whitespace(line[i])))
		i++;
	if (!line[i])
	{
		free(line - 3);
		error_exit(env, ERROR_MSG_MISSING_TEXTURE_FILE,
			ERROR_CODE_FILE_SYSTEM_ERROR);
	}
	path = ft_strdup(&line[i]);
	if (!path)
	{
		free(line - 3);
		error_exit(env, ERROR_MSG_MAP_ALLOCATION_FAILED,
			ERROR_CODE_FILE_SYSTEM_ERROR);
	}
	i = ft_strlen(path) - 1;
	while (i >= 0 && (is_whitespace(path[i])))
		path[i--] = '\0';
	*texture = path;
}

void	map_parse_one_element(char *line, t_env *env)
{
	while (is_whitespace(*line))
		line++;
	if (map_check_valid_texture_element(line, MAP_NORTH_TEXTURE,
			env->map.no_texture, env))
		return (parse_texture(line + 3, &env->map.no_texture, env));
	else if (map_check_valid_texture_element(line, MAP_SOUTH_TEXTURE,
			env->map.so_texture, env))
		return (parse_texture(line + 3, &env->map.so_texture, env));
	else if (map_check_valid_texture_element(line, MAP_EAST_TEXTURE,
			env->map.ea_texture, env))
		return (parse_texture(line + 3, &env->map.ea_texture, env));
	else if (map_check_valid_texture_element(line, MAP_WEST_TEXTURE,
			env->map.we_texture, env))
		return (parse_texture(line + 3, &env->map.we_texture, env));
	else if (map_check_valid_color_element(line, MAP_FLOOR_COLOR,
			env->map.floor_color, env))
		return (parse_rgb(line + 2, &env->map.floor_color, env));
	else if (map_check_valid_color_element(line, MAP_CEILING_COLOR,
			env->map.ceiling_color, env))
		return (parse_rgb(line + 2, &env->map.ceiling_color, env));
	free(line);
	error_exit(env, ERROR_MSG_UNEXPECTED_FILE_LINE,
		ERROR_CODE_FILE_SYSTEM_ERROR);
}

void	map_check_all_elements_parsed(char *line, t_env *env)
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
	if (env->map.ceiling_color == -1)
		return (free(line), error_exit(env, ERROR_MSG_MISSING_CEILING_COLOR,
				ERROR_CODE_FILE_SYSTEM_ERROR));
	if (env->map.floor_color == -1)
		return (free(line), error_exit(env, ERROR_MSG_MISSING_FLOOR_COLOR,
				ERROR_CODE_FILE_SYSTEM_ERROR));
}

void	map_parse(t_env *env, char *map_file_path)
{
	char	*line;
	bool	map_started;

	env->map.map_file_fd = open(map_file_path, O_RDONLY);
	if (env->map.map_file_fd < 0)
		return (error_exit(env, ERROR_MSG_UNABLE_TO_OPEN_FILE,
				ERROR_CODE_FILE_SYSTEM_ERROR));
	map_started = false;
	while (true)
	{
		line = get_next_line(env->map.map_file_fd);
		if (!line)
			break ;
		if (is_empty_line(line))
		{
			free(line);
			continue ;
		}
		if (line[0] == MAP_SPACE || line[0] == MAP_WALL)
		{
			map_check_all_elements_parsed(line, env);
			map_started = 1;
			free(line); //obrisi samo privremeno za testiranje
			// TODO: map_parse_matrix(env,fd); dont close fd in this function its already closed afterwards in current function
			break ;
		}
		map_parse_one_element(line, env);
		free(line);
	}
	close(env->map.map_file_fd);
	env->map.map_file_fd = -1;
	if (!map_started)
		error_exit(env, ERROR_MSG_NO_MAP_FOUND_IN_FILE,
			ERROR_CODE_FILE_SYSTEM_ERROR);
}
