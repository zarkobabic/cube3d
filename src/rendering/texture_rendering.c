/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_rendering.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkau <eberkau@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 23:27:26 by eberkau           #+#    #+#             */
/*   Updated: 2025/12/06 04:39:41 by eberkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	get_pixel_from_texture(const mlx_texture_t *tex, unsigned int x,
	unsigned int y)
{
	uint32_t		pixel_value;
	unsigned int	pix_pos;

	if (!tex || !tex->pixels || x >= tex->width || y >= tex->height
		|| tex->bytes_per_pixel < 3 || tex->bytes_per_pixel > 4)
		return (0xFF00FF00);
	pix_pos = (y * tex->width + x) * tex->bytes_per_pixel;
	pixel_value = 0;
	pixel_value = ((uint32_t)tex->pixels[pix_pos + 0] << 24)
		| ((uint32_t)tex->pixels[pix_pos + 1] << 16)
		| ((uint32_t)tex->pixels[pix_pos + 2] << 8);
	if (tex->bytes_per_pixel == 4)
		pixel_value |= tex->pixels[pix_pos + 3];
	else
		pixel_value |= 0xFF;
	return (pixel_value);
}

static void	draw_wall_column(const t_env *env, t_tex_draw *draw)
{
	double			tex_y;
	double			tex_y_step;
	int				y;

	tex_y_step = (double)draw->texture->height / draw->proj_height;
	tex_y = 0;
	if (draw->start_y < 0)
	{
		tex_y = -draw->start_y * tex_y_step;
		draw->start_y = 0;
	}
	if (draw->end_y >= env->win_height)
		draw->end_y = env->win_height - 1;
	y = draw->start_y;
	while (y <= draw->end_y)
	{
		mlx_put_pixel(env->img, draw->x, y,
			get_pixel_from_texture(draw->texture, draw->tex_x,
				(unsigned int)tex_y));
		tex_y += tex_y_step;
		++y;
	}
}

static mlx_texture_t	*select_texture(const t_env *env, int wall_dir)
{
	if (wall_dir == WALL_NORTH)
		return (env->map.textures.no.mlx_tex);
	else if (wall_dir == WALL_SOUTH)
		return (env->map.textures.so.mlx_tex);
	else if (wall_dir == WALL_EAST)
		return (env->map.textures.ea.mlx_tex);
	else
		return (env->map.textures.we.mlx_tex);
}

static void	setup_tex_draw(t_tex_draw *draw, const t_point *wall_pos,
				const t_point *wall_start, const t_point *wall_end)
{
	double	wall_hit_offset;
	double	wall_frac;

	draw->x = wall_start->x;
	draw->start_y = wall_start->y;
	draw->end_y = wall_end->y;
	if (draw->wall_dir == WALL_NORTH || draw->wall_dir == WALL_SOUTH)
		wall_hit_offset = (double)(wall_pos->x % draw->tile_size);
	else
		wall_hit_offset = (double)(wall_pos->y % draw->tile_size);
	if (draw->wall_dir == WALL_SOUTH || draw->wall_dir == WALL_WEST)
		wall_hit_offset = (double)(draw->tile_size - wall_hit_offset);
	wall_frac = wall_hit_offset / draw->tile_size;
	draw->tex_x = (unsigned int)(wall_frac * draw->texture->width);
	if (draw->tex_x >= draw->texture->width)
		draw->tex_x = draw->texture->width - 1;
}

void	draw_texture(const t_env *env, const t_ray_tex_data *data)
{
	t_tex_draw	draw;

	draw.wall_dir = data->wall_dir;
	draw.texture = select_texture(env, data->wall_dir);
	draw.proj_height = data->proj_height;
	draw.tile_size = data->tile_size;
	setup_tex_draw(&draw, data->wall_pos, data->wall_start, data->wall_end);
	draw_wall_column(env, &draw);
}
