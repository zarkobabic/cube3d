/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:15:43 by zbabic            #+#    #+#             */
/*   Updated: 2025/11/07 21:09:51 by zbabic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "error.h"

#define MAP_FILE_PATH_INDEX 1

int main(int argc, char **argv)
{
	t_env	env;

	if(argc != 2)
		return perror(ERROR_MSG_WRONG_NUMBER_OF_PARAMETERS), 1;
	env_init(&env);
	map_parse_check_file_extension(&env, argv[MAP_FILE_PATH_INDEX]);
	map_parse(&env, argv[MAP_FILE_PATH_INDEX]);
	//mlx_initialization(&env);
	env_destroy(&env);
	return 0;
}