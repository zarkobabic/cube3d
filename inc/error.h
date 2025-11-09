/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:47:04 by zbabic            #+#    #+#             */
/*   Updated: 2025/11/09 22:50:30 by zbabic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "cube3d.h"

# define ERROR_MSG_WRONG_NUMBER_OF_PARAMETERS  \
"Error\n Invalid number of parameters. Expected exactly 2 parameters."
# define ERROR_MSG_MLX_MEMORY_ALLOCATION_FAILED \
"Error\n Memory allocation failure in MLX library."
# define ERROR_MSG_MLX_WINDOW_CREATION_FAILED \
"Error\n Window creation failed in MLX library."
# define ERROR_MSG_WRONG_FILE_EXTENSION \
"Error\n Invalid file extension. Expected a .pub map file."
# define ERROR_MSG_MLX_INIT_FAIL \
"Error\n MLX library initialization failed."
# define ERROR_MSG_UNABLE_TO_OPEN_FILE \
"Error\n Unable to open the specified file."
# define ERROR_MSG_NO_MAP_FOUND_IN_FILE \
"Error\n No map found in specified file."
# define ERROR_MSG_MISSING_NO_TEXTURE \
"Error\n Missing north texture file path in specified file"
# define ERROR_MSG_MISSING_SO_TEXTURE \
"Error\n Missing south texture file path in specified file"
# define ERROR_MSG_MISSING_WE_TEXTURE \
"Error\n Missing west texture file path in specified file"
# define ERROR_MSG_MISSING_EA_TEXTURE \
"Error\n Missing east texture file path in specified file"
# define ERROR_MSG_MISSING_FLOOR_COLOR \
"Error\n Floor color is not specified in specified file"
# define ERROR_MSG_MISSING_CEILING_COLOR \
"Error\n Ceiling color is not specified in specified file"
# define ERROR_MSG_MULTIPLE_DEFINITION_NO_TEXTURE \
"Error\n Specified file contains multiple definitions of north texture"
# define ERROR_MSG_MULTIPLE_DEFINITION_SO_TEXTURE \
"Error\n Specified file contains multiple definitions of south texture"
# define ERROR_MSG_MULTIPLE_DEFINITION_WE_TEXTURE \
"Error\n Specified file contains multiple definitions of west texture"
# define ERROR_MSG_MULTIPLE_DEFINITION_EA_TEXTURE \
"Error\n Specified file contains multiple definitions of east texture"
# define ERROR_MSG_MULTIPLE_DEFINITION_FLOOR_COLOR \
"Error\n Specified file contains multiple definitions of floor color"
# define ERROR_MSG_MULTIPLE_DEFINITION_CEILING_COLOR \
"Error\n Specified file contains multiple definitions of ceiling color"
# define ERROR_MSG_UNEXPECTED_FILE_LINE \
"Error\n Unexpected file line"
# define ERROR_MSG_MISSING_TEXTURE_FILE \
"Error\n Missing texture file path"
# define ERROR_MSG_MAP_ALLOCATION_FAILED \
"Error\n Map allocation failed"
# define ERROR_MSG_COLOR_PARSING_FAILED \
"Error\n Color parsing from specified file failed"
# define ERROR_MSG_WRONG_COLOR_FORMAT \
"Error\n Color format is wrong. Color must have defined R G and B values"
# define ERROR_MSG_WRONG_COLOR_COMPONENT_RANGE \
"Error\n Wrong color component range. RGB values must be between 0 and 255"
# define ERROR_MSG_MATRIX_READ_FAIL \
"Error\n Failed to read map matrix data."
# define ERROR_MSG_MATRIX_ALLOCATION_FAIL \
"Error\n Failed to allocate space for map matrix data."
# define ERROR_MSG_INVALID_PLAYER_COUNT \
"Error\n Invalid map configuration: exactly one player must be defined."
# define ERROR_MSG_MAP_RULES_VIOLATION \
"Error\n Invalid map configuration: the map must be fully enclosed by walls, \
and the player must be located within the enclosed area."

typedef enum e_error_code
{
	ERROR_CODE_NO_ERROR,
	ERROR_CODE_GENERAL_ERROR,
	ERROR_CODE_FILE_SYSTEM_ERROR,
	ERROR_CODE_MLX_ERROR,
	ERROR_MAP_READ_ERROR
}		t_error_code;

void	error_exit(t_env *env, const char *message, t_error_code error_code);

#endif