/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_single_element_parsing.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 21:20:29 by zbabic            #+#    #+#             */
/*   Updated: 2025/11/11 11:13:48 by zbabic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "error.h"

static void	free_split(char ***split)
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
		return (free(line - 2), free_split(&split), error_exit(env,
				ERROR_MSG_WRONG_COLOR_COMPONENT_RANGE,
				ERROR_CODE_FILE_SYSTEM_ERROR));
	*color_loc_to_fill = (rgb[COLOR_R] << 16 | rgb[COLOR_G] << 8
			| rgb[COLOR_B]);
	free_split(&split);
}

//TODO: Maybe needs check if its readable texture file with open and O_READ
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
