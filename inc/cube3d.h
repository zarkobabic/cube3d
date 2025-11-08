/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:05:55 by zbabic            #+#    #+#             */
/*   Updated: 2025/11/07 21:24:36 by zbabic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "MLX42.h"
# include "libft.h"
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

# define WINDOW_WIDTH 1000
# define WINDOW_HEIGHT 500

# define MAP_EMPTY '0'
# define MAP_WALL '1'
# define MAP_SPACE ' '
# define MAP_PLAYER_NORTH 'N'
# define MAP_PLAYER_EAST 'E'
# define MAP_PLAYER_WEST 'W'
# define MAP_PLAYER_SOUTH 'S'
# define MAP_NORTH_TEXTURE "NO "
# define MAP_SOUTH_TEXTURE "SO "
# define MAP_EAST_TEXTURE "EA "
# define MAP_WEST_TEXTURE "WE "
# define MAP_FLOOR_COLOR "F "
# define MAP_CEILING_COLOR "C "

# define COLOR_R 0
# define COLOR_G 1
# define COLOR_B 2

typedef struct s_player
{
	int			coordinates[2];
	char		player_dir;
}				t_player;

typedef struct s_map
{
	int			map_file_fd;
	int			rows;
	int			cols;
	int			tile_size;
	char		**matrix;
	char		*no_texture;
	char		*so_texture;
	char		*we_texture;
	char		*ea_texture;
	int			floor_color;
	int			ceiling_color;
	t_player	player;
}				t_map;

typedef struct s_env
{
	mlx_image_t	*img;
	mlx_t		*win;
	int			win_height;
	int			win_width;
	t_map		map;
}				t_env;

// MLX
void			mlx_initialization(t_env *env);
// ENV
void			env_init(t_env *env);
void			env_destroy(t_env *env);
// MAP
void			map_destroy(t_map *map);
void			map_init(t_env *env);
// MAP_PARSING
void			map_parse(t_env *env, char *map_file_path);
void			map_parse_check_file_extension(t_env *env, char *map_file_path);
// PLAYER
void			player_init(t_player *player);
#endif