/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:05:55 by zbabic            #+#    #+#             */
/*   Updated: 2025/12/06 16:02:59 by zbabic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42.h"
# include "libft.h"
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

# define WINDOW_WIDTH 4000
# define WINDOW_HEIGHT 4000
# define TILE_SIZE 30
# define FOV 60
# define PLAYER_RADIUS 2
# define ROTATION_SPEED 0.03
# define MOVE_SPEED 0.08
# define RES 1
# define WALL_HEIGHT 100
# define MINIMAP_RATIO 0.4
# define MINIMAP_MARGIN 5

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

# define ORIENT_SOUTH 0
# define ORIENT_EAST 1
# define WALL_HOR 0
# define WALL_VER 1
# define WALL_NORTH 0
# define WALL_SOUTH 1
# define WALL_EAST 2
# define WALL_WEST 3

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

typedef struct s_tex_draw
{
	int				x;
	int				start_y;
	int				end_y;
	unsigned int	tex_x;
	int				wall_dir;
	mlx_texture_t	*texture;
	double			proj_height;
	int				tile_size;
}					t_tex_draw;

typedef struct s_ray_tex_data
{
	const t_point	*wall_pos;
	const t_point	*wall_start;
	const t_point	*wall_end;
	double			proj_height;
	int				wall_dir;
	int				tile_size;
}					t_ray_tex_data;

typedef struct s_ray_hit
{
	t_point_double	at[2];
	bool			found[2];
}					t_ray_hit;

typedef struct s_ray_render_params
{
	double			ray_angle;
	int				column;
	int				wall_dir;
}					t_ray_render_params;

typedef struct s_texture
{
	char			*path;
	mlx_texture_t	*mlx_tex;
}					t_texture;

typedef struct s_tex_group
{
	t_texture		no;
	t_texture		so;
	t_texture		we;
	t_texture		ea;
}					t_tex_group;

typedef struct s_keys
{
	int				w_pressed;
	int				a_pressed;
	int				s_pressed;
	int				d_pressed;
	int				left_arrow;
	int				right_arrow;
	int				lshift;
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
	int				minimap_tile_size;
	int				minimap_position_x;
	int				minimap_position_y;
	unsigned int	floor_color;
	unsigned int	ceiling_color;
	t_tex_group		textures;
	bool			floor_color_set;
	bool			ceiling_color_set;
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

void	mlx_initialization(t_env *env);
void	mlx_destroy(t_env *env);

// ENV

void	env_init(t_env *env);
void	env_destroy(t_env *env);

// MAP

void	map_destroy(t_map *map);
void	map_init(t_env *env);
void	map_resize_screen(t_env *env);

// PLAYER

void	player_init(t_player *player);
void	player_set_starting_orientation(t_player *player,
			char starting_orientation);

//----PARSING----

// FILE_PARSING

bool	is_whitespace(char c);
void	file_parsing(t_env *env, const char *map_file_path);
void	file_check_extension(t_env *env, char *file_path, char *extension,
			const char *err_msg);

// FILE_ELEMENTS_PARSING

void	file_check_all_elements_parsed(char *line, t_env *env);
void	file_parse_one_element(char *line, t_env *env);

// FILE_SINGLE_ELEMENT_PARSING

void	parse_texture(char *line, char **texture, t_env *env);
void	parse_rgb(char *line, unsigned int *color_loc_to_fill,
			bool *flag_to_set, t_env *env);

// MAP_PARSING

void	map_parsing(t_env *env, char *first_line);
char	*map_pad_line_with_spaces(char *line, int target_width);

// MAP_VALIDATION

bool	map_validate_char(char c);
bool	map_validate_rules(const t_map *map);
bool	map_validate_player(t_map *map);

// TEXTURE_LOADING

void	load_textures(t_env *env);

//---------------

// SCENE_RENDERING

void	reset_background(const t_env *env);
void	render_scene(const t_env *env);
void	render_ceiling(const t_env *env, t_point *wall_end);
void	render_floor(const t_env *env, t_point *wall_end);

// ELEMENTS_RENDERING

void	draw_square(const t_env *env, int size, const t_point *left_corner,
			unsigned int color);
void	draw_filled_circle(const t_env *env, const t_point_double *center,
			int radius, int color);
// LINE_RENDERING

void	draw_line(const t_env *env, const t_point *starting,
			const t_point *ending, int color);

// RAY RENDERING

void	render_all_rays(const t_env *env, int num_rays);

// TEXTURE_RENDERING

void	draw_texture(const t_env *env, const t_ray_tex_data *data);

// RAYCASTING

int		cast_ray(double ray_angle, t_point *wall_collision_point,
			const t_env *env);
double	get_distance_squared(const t_point_double *point,
			const t_point_double *player_pos);
double	normalize_angle(double angle);
int		select_closest_wall(t_point *wall_collision_point, t_ray_hit *hit,
			const t_env *env, double ray_angle);

// MINIMAP

void	init_minimap(t_env *env);
void	draw_minimap(const t_env *env);
bool	has_wall_at(const t_env *env, const t_point *point_in_pixel);
void	render_all_rays_minimap(const t_env *env, int num_rays);

// UTILITIES

double	deg_to_rad(int degrees);

//--------------

// GAME_LOOP

void	game_loop(void *param);

// KEY_HANDLER

void	key_handler(mlx_key_data_t keydata, void *param);

#endif