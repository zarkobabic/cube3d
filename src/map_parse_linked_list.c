/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_linked_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 16:07:11 by zbabic            #+#    #+#             */
/*   Updated: 2025/11/09 00:04:35 by zbabic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

t_map_line	*create_map_node(char *line)
{
	t_map_line	*node;

	node = malloc(sizeof(t_map_line));
	if (!node)
		return (NULL);
	node->line = line;
	node->next = NULL;
	return (node);
}

void	add_map_line(t_map_line **head, t_map_line **tail,
		t_map_line *new_node)
{
	if (!*head)
	{
		*head = new_node;
		*tail = new_node;
		return ;
	}
	(*tail)->next = new_node;
	*tail = new_node;
}

void	free_map_list(t_map_line **head)
{
	t_map_line	*tmp;

	while (head && *head)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp->line);
		free(tmp);
	}
}
