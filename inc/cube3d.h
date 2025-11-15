/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:05:55 by zbabic            #+#    #+#             */
/*   Updated: 2025/11/15 02:08:34 by zbabic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "MLX42.h"
# include "libft.h"
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

# define WINDOW_WIDTH 1000
# define WINDOW_HEIGHT 500
# define TILE_SIZE 30
# define FOV 60
# define PLAYER_RADIUS 2
# define ROTATION_SPEED 0.05
# define MOVE_SPEED 1
# define RES 1

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
# define COLOR_WALL 0
# define COLOR_EMPTY 0xFFFFFFFF
# define COLOR_PLAYER 0xff4040d9
# define COLOR_SPACE 0x00000059
# define COLOR_BACKGROUND 0xFF

typedef struct s_point
{
	int				x;
	int				y;
}					t_point;

typedef struct s_point_double
{
	double			x;
	double			y;
}					t_point_double;

typedef struct s_keys
{
	int				w_pressed;
	int				a_pressed;
	int				s_pressed;
	int				d_pressed;
	int				left_arrow;
	int				right_arrow;
}					t_keys;

typedef struct s_player
{
	t_point_double	pos;
	t_keys			keys;
	double			fov_rad;
	double			rot_angle;
	double			rot_speed;
	double			move_speed;
}					t_player;

typedef struct s_map
{
	int				map_file_fd;
	int				rows;
	int				cols;
	int				tile_size;
	char			**matrix;
	char			*no_texture;
	char			*so_texture;
	char			*we_texture;
	char			*ea_texture;
	int				floor_color;
	int				ceiling_color;
	t_player		player;
}					t_map;

typedef struct s_env
{
	mlx_image_t		*img;
	mlx_t			*win;
	int				win_height;
	int				win_width;
	t_map			map;
}					t_env;

// MLX
void				mlx_initialization(t_env *env);
void				mlx_destroy(t_env *env);
// ENV
void				env_init(t_env *env);
void				env_destroy(t_env *env);
// MAP
void				map_destroy(t_map *map);
void				map_init(t_env *env);
// TODO: just for testing delete after
void				test_map_print(t_env *env);
// PLAYER
void				player_init(t_player *player);
void				player_set_starting_orientation(t_player *player,
						char starting_orientation);

//----PARSING----

// FILE_PARSING
bool				is_whitespace(char c);
void				file_parsing(t_env *env, char *map_file_path);
void				file_check_extension(t_env *env, char *map_file_path);
// FILE_ELEMENTS_PARSING
void				file_check_all_elements_parsed(char *line, t_env *env);
void				file_parse_one_element(char *line, t_env *env);
// FILE_SINGLE_ELEMENT_PARSING
void				parse_texture(char *line, char **texture, t_env *env);
void				parse_rgb(char *line, int *color_loc_to_fill, t_env *env);
// MAP_PARSING
void				map_parsing(t_env *env, char *first_line);
char				*map_pad_line_with_spaces(char *line, int target_width);
// MAP_VALIDATION
bool				map_validate_char(char c);
bool				map_validate_rules(t_map *map);
bool				map_validate_player(t_map *map);

//---------------

// SCENE_RENDERING
void				reset_background(t_env *env);
void				render_scene(t_env *env);

// ELEMENTS_RENDERING
void				draw_square(t_env *env, int size, t_point *left_corner,
						unsigned int color);
void				draw_filled_circle(t_env *env, t_point_double *center,
						int radius, int color);
// LINE_RENDERING
void				draw_line(t_env *env, t_point *starting, t_point *ending,
						int color);
// RAY RENDERING
void				render_all_rays(t_env *env, int num_rays);
// RAYCASTING
void				cast_ray(double ray_angle, t_point *wall_collision_point,
						t_env *env);
// MINIMAP
void				init_minimap(t_env *env);
void				draw_minimap(t_env *env);
bool				has_wall_at(t_env *env, t_point *point_in_pixel);
// UTILITIES
double				deg_to_rad(int degrees);
//--------------

// GAME_LOOP
void				game_loop(void *param);
// KEY_HANDLER
void				key_handler(mlx_key_data_t keydata, void *param);

#endif