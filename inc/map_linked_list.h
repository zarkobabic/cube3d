/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_linked_list.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 22:48:51 by zbabic            #+#    #+#             */
/*   Updated: 2025/11/08 22:52:17 by zbabic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_LINKED_LIST_H
# define MAP_LINKED_LIST_H

typedef struct s_map_line
{
	char				*line;
	struct s_map_line	*next;
}						t_map_line;

t_map_line				*create_map_node(char *line);
void					add_map_line(t_map_line **head, t_map_line **tail,
							t_map_line *new_node);
void					free_map_list(t_map_line **head);

#endif