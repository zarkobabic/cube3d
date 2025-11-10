/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_linked_list.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 22:48:51 by zbabic            #+#    #+#             */
/*   Updated: 2025/11/10 21:47:00 by zbabic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_LINKED_LIST_H
# define MAP_LINKED_LIST_H

# include "cube3d.h"

typedef struct s_map_line
{
	char				*line;
	struct s_map_line	*next;
}						t_map_line;

t_map_line				*map_list_create_node(char *line);
void					map_list_add(t_map_line **head, t_map_line **tail,
							t_map_line *new_node);
void					map_list_free(t_map_line **head);
bool					map_list_to_matrix(t_map_line *head, t_env *env);

#endif