/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:05:55 by zbabic            #+#    #+#             */
/*   Updated: 2025/11/03 17:39:33 by zbabic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
#define CUBE3D_H

# include <stdlib.h>
# include "MLX42.h"

# define WIDTH 1000
# define HEIGHT 500

typedef struct s_map
{
	mlx_image_t		*img;
	mlx_t			*win;
}					t_map;

void	initialization_mlx(t_map *map);
void	map_destructor(t_map *map);

#endif