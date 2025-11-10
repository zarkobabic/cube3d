/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 15:25:19 by zbabic            #+#    #+#             */
/*   Updated: 2025/11/10 21:44:45 by zbabic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "error.h"
#include "map_linked_list.h"

static bool	map_validate_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (!map_validate_char(line[i]))
			return (false);
		i++;
	}
	return (true);
}

static bool	map_read_lines(t_map_line **head, char *first_line, t_env *env)
{
	char		*line;
	t_map_line	*new_node;
	t_map_line	*tail;

	tail = NULL;
	env->map.rows = 0;
	line = first_line;
	while (true)
	{
		if (!line)
			break ;
		if (!map_validate_line(line))
			return (free(line), false);
		new_node = map_list_create_node(line);
		if (!new_node)
			return (free(line), false);
		map_list_add(head, &tail, new_node);
		++(env->map.rows);
		line = get_next_line(env->map.map_file_fd);
	}
	return (true);
}

static int	map_get_max_line_length(t_map_line *head)
{
	int		max_len;
	int		len;
	char	*line;

	max_len = 0;
	while (head)
	{
		line = head->line;
		len = 0;
		while (line[len] && line[len] != '\n')
			len++;
		if (len > max_len)
			max_len = len;
		head = head->next;
	}
	return (max_len);
}

char	*map_pad_line_with_spaces(char *line, int target_width)
{
	char	*padded;
	int		i;
	int		len;

	len = 0;
	while (line[len] && line[len] != '\n')
		++len;
	padded = malloc(target_width + 1);
	if (!padded)
		return (NULL);
	i = 0;
	while (i < len)
	{
		padded[i] = line[i];
		++i;
	}
	while (i < target_width)
	{
		padded[i] = ' ';
		++i;
	}
	padded[i] = '\0';
	return (padded);
}

void	map_parsing(t_env *env, char *first_line)
{
	t_map_line	*head;

	head = NULL;
	if (!map_read_lines(&head, first_line, env))
		return (map_list_free(&head), error_exit(env,
				ERROR_MSG_MATRIX_READ_FAIL, ERROR_MAP_READ_ERROR));
	if (!head)
		return (error_exit(env, ERROR_MSG_MATRIX_READ_FAIL,
				ERROR_MAP_READ_ERROR));
	env->map.cols = map_get_max_line_length(head);
	if (!map_list_to_matrix(head, env))
		return (map_list_free(&head), error_exit(env,
				ERROR_MSG_MATRIX_ALLOCATION_FAIL, ERROR_MAP_READ_ERROR));
	map_list_free(&head);
	if (!map_validate_player(&env->map))
		error_exit(env, ERROR_MSG_INVALID_PLAYER_COUNT, ERROR_MAP_READ_ERROR);
	if (!map_validate_rules(&env->map))
		error_exit(env, ERROR_MSG_MAP_RULES_VIOLATION, ERROR_MAP_READ_ERROR);
}
