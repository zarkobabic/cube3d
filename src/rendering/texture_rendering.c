/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_rendering.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkau <eberkau@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 23:27:26 by eberkau           #+#    #+#             */
/*   Updated: 2025/11/30 23:46:34 by eberkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	get_pixel_from_texture(const mlx_texture_t *tex, unsigned int x, unsigned int y)
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

void hori_walls(const t_env *env, const t_point *wall_collision_p, mlx_texture_t *texture, t_point *wall_start, t_point *wall_end, double projected_wall_height)
{
	unsigned int	tex_x;
	unsigned int	tex_y_min;
	unsigned int	tex_y_max;
	double			tex_y_step;

	tex_x = (wall_collision_p->x - env->map.tile_size) % texture->width;

	tex_y_min = 0;
	tex_y_max = texture->height - 1;

	tex_y_step = (double)texture->height / projected_wall_height;


	double real_wall_top;
	{
		real_wall_top = env->win_height / 2.0 - projected_wall_height / 2.0;
		
		if (wall_start->y < 0)
		{
			tex_y_min = (-real_wall_top / projected_wall_height)
			* texture->height;
			wall_start->y = 0;
		}
	} // FIXME: ChatGPT suggestion but doesn't fix destortion when close to wall


	// if (wall_start->y < 0)
	// {
	// 	tex_y_min -= wall_start->y * tex_y_step;
	// 	wall_start->y = 0;
	// }
	if (wall_end->y >= env->win_height) // FIXME: should be the same as previous 'if', as value and as calculation (symmetric on horizon) -> combine for fewer function args
	{
		// tex_y_max -= (wall_end->y - env->win_height) * tex_y_step;
		wall_end->y = env->win_height;
	}

	double i = tex_y_min;
	int line_y = wall_start->y;

	while (i <= tex_y_max && line_y >= 0 && line_y < env->win_height)
	{
		mlx_put_pixel(env->img, wall_start->x, line_y, get_pixel_from_texture(texture, tex_x, (unsigned int)i));
		i += tex_y_step;
		line_y += 1;
	}
}

void verti_walls(const t_env *env, const t_point *wall_collision_p, mlx_texture_t *texture, t_point *wall_start, t_point *wall_end, double projected_wall_height)
{
	unsigned int	tex_x;
	unsigned int	tex_y_min;
	unsigned int	tex_y_max;
	double			tex_y_step;

	tex_x = (wall_collision_p->y - env->map.tile_size) % texture->width;

	tex_y_min = 0;
	tex_y_max = texture->height - 1;

	tex_y_step = (double)texture->height / projected_wall_height;

	double real_wall_top;
	{
		real_wall_top = env->win_height / 2.0 - projected_wall_height / 2.0;
		
		if (wall_start->y < 0)
		{
			tex_y_min = (-real_wall_top / projected_wall_height)
			* texture->height;
			wall_start->y = 0;
		}
	} // FIXME: ChatGPT suggestion but doesn't fix destortion when close to wall


	// if (wall_start->y < 0)
	// {
	// 	tex_y_min -= wall_start->y * tex_y_step;
	// 	wall_start->y = 0;
	// }
	if (wall_end->y >= env->win_height) // FIXME: should be the same as previous 'if', as value and as calculation (symmetric on horizon) -> combine for fewer function args
	{
		// tex_y_max -= (wall_end->y - env->win_height) * tex_y_step;
		wall_end->y = env->win_height;
	}

	double i = tex_y_min;
	int line_y = wall_start->y;

	while (i <= tex_y_max && line_y >= 0 && line_y < env->win_height)
	{
		mlx_put_pixel(env->img, wall_start->x, line_y, get_pixel_from_texture(texture, tex_x, (unsigned int)i));
		i += tex_y_step;
		line_y += 1;
	}
}

void paint_textures(const t_env *env, const t_point *wall_collision_p, t_point *wall_start, t_point *wall_end, double projected_wall_height)
{
	if (env->map.matrix[wall_collision_p->y / env->map.tile_size][wall_collision_p->x / env->map.tile_size - 1] == MAP_WALL
			&& env->map.matrix[wall_collision_p->y / env->map.tile_size][wall_collision_p->x / env->map.tile_size + 1] == MAP_WALL) // FIXME: condition not right
		hori_walls(env, wall_collision_p, env->map.textures.no.mlx_tex, wall_start, wall_end, projected_wall_height);
	else
		verti_walls(env, wall_collision_p, env->map.textures.we.mlx_tex, wall_start, wall_end, projected_wall_height);
}
// BUG: fisheye effect still somewhat present, evaluate
// FIXME: mirrored texture on oppposite walls