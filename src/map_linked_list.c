/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_linked_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 16:07:11 by zbabic            #+#    #+#             */
/*   Updated: 2025/11/10 21:40:22 by zbabic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "map_linked_list.h"

t_map_line	*map_list_create_node(char *line)
{
	t_map_line	*node;

	node = malloc(sizeof(t_map_line));
	if (!node)
		return (NULL);
	node->line = line;
	node->next = NULL;
	return (node);
}

void	map_list_add(t_map_line **head, t_map_line **tail,
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

void	map_list_free(t_map_line **head)
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

bool	map_list_to_matrix(t_map_line *head, t_env *env)
{
	int			i;
	t_map_line	*current;

	env->map.matrix = malloc(sizeof(char *) * (env->map.rows));
	if (!env->map.matrix)
		return (false);
	i = 0;
	current = head;
	while (current && i < env->map.rows)
	{
		env->map.matrix[i] = map_pad_line_with_spaces(current->line,
				env->map.cols);
		if (!env->map.matrix[i])
			return (false);
		current = current->next;
		++i;
	}
	return (true);
}
