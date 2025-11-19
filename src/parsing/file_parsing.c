/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkau <eberkau@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:32:03 by zbabic            #+#    #+#             */
/*   Updated: 2025/11/19 18:13:54 by eberkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "error.h"
#include <fcntl.h>
#include <unistd.h>

void	file_check_extension(t_env *env, char *map_file_path)
{
	int		has_no_extension;
	size_t	len;

	len = ft_strlen(map_file_path);
	if (len < 4)
		error_exit(env, ERROR_MSG_WRONG_FILE_EXTENSION,
			ERROR_CODE_FILE_SYSTEM_ERROR);
	has_no_extension = ft_strncmp(&map_file_path[len - 4], ".cub", 5);
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

static bool	file_is_empty_line(char *line)
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

static void	file_process_lines(bool *map_started, t_env *env)
{
	char	*line;

	while (true)
	{
		line = get_next_line(env->map.map_file_fd);
		if (!line)
			return ;
		if (file_is_empty_line(line))
		{
			free(line);
			continue ;
		}
		if (line[0] == MAP_SPACE || line[0] == MAP_WALL)
		{
			file_check_all_elements_parsed(line, env);
			*map_started = 1;
			map_parsing(env, line);
			return ;
		}
		file_parse_one_element(line, env);
		free(line);
	}
}

void	file_parsing(t_env *env, char *map_file_path)
{
	bool	map_started;

	env->map.map_file_fd = open(map_file_path, O_RDONLY);
	if (env->map.map_file_fd < 0)
		return (error_exit(env, ERROR_MSG_UNABLE_TO_OPEN_FILE,
				ERROR_CODE_FILE_SYSTEM_ERROR));
	map_started = false;
	file_process_lines(&map_started, env);
	close(env->map.map_file_fd);
	env->map.map_file_fd = -1;
	if (!map_started)
		error_exit(env, ERROR_MSG_NO_MAP_FOUND_IN_FILE,
			ERROR_CODE_FILE_SYSTEM_ERROR);
}
