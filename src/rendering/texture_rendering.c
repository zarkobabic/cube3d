/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_rendering.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkau <eberkau@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 23:27:26 by eberkau           #+#    #+#             */
/*   Updated: 2025/11/27 00:31:19 by eberkau          ###   ########.fr       */
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
