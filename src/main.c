/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:15:43 by zbabic            #+#    #+#             */
/*   Updated: 2025/12/06 15:58:18 by zbabic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "error.h"

#define MAP_FILE_PATH_INDEX 1

int	main(int argc, char **argv)
{
	t_env	env;

	if (argc != 2)
		return (perror(ERROR_MSG_WRONG_NUMBER_OF_PARAMETERS), 1);
	env_init(&env);
	file_check_extension(&env, argv[MAP_FILE_PATH_INDEX], ".cub",
		ERROR_MSG_WRONG_MAP_FILE_EXTENSION);
	file_parsing(&env, argv[MAP_FILE_PATH_INDEX]);
	map_resize_screen(&env);
	init_minimap(&env);
	mlx_initialization(&env);
	render_scene(&env);
	mlx_loop(env.win);
	mlx_destroy(&env);
	env_destroy(&env);
	return (0);
}
