/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 20:51:55 by zbabic            #+#    #+#             */
/*   Updated: 2025/11/10 21:33:59 by zbabic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "error.h"

bool	map_validate_char(char c)
{
	return (c == MAP_EMPTY || c == MAP_WALL || c == MAP_SPACE
		|| c == MAP_PLAYER_NORTH || c == MAP_PLAYER_SOUTH
		|| c == MAP_PLAYER_EAST || c == MAP_PLAYER_WEST);
}

static int	map_validate_player_char(char c)
{
	return (c == MAP_PLAYER_NORTH || c == MAP_PLAYER_SOUTH
		|| c == MAP_PLAYER_EAST || c == MAP_PLAYER_WEST);
}

static int	map_validate_character_on_position(t_map *map, int i, int j)
{
	if (map->matrix[i][j] != MAP_EMPTY
		&& !map_validate_player_char(map->matrix[i][j]))
		return (true);
	if (i == 0 || i == map->rows - 1)
		return (false);
	if (j == 0 || j == map->cols - 1)
		return (false);
	if (map->matrix[i - 1][j] == MAP_SPACE || map->matrix[i
		+ 1][j] == MAP_SPACE)
		return (false);
	if (map->matrix[i][j - 1] == MAP_SPACE || map->matrix[i][j
		+ 1] == MAP_SPACE)
		return (false);
	return (true);
}

bool	map_validate_rules(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	while (++i < map->rows)
	{
		j = -1;
		while (++j < map->cols)
			if (!map_validate_character_on_position(map, i, j))
				return (false);
	}
	return (true);
}

bool	map_validate_player(t_map *map)
{
	int	i;
	int	j;
	int	player_count;

	player_count = 0;
	i = -1;
	while (++i < map->rows)
	{
		j = -1;
		while (++j < map->cols)
		{
			if (map_validate_player_char(map->matrix[i][j]))
			{
				map->player.coordinates[0] = i;
				map->player.coordinates[1] = j;
				map->player.player_dir = map->matrix[i][j];
				player_count++;
			}
		}
	}
	if (player_count != 1)
		return (false);
	return (true);
}
