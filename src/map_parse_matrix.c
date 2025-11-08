/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_matrix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 15:25:19 by zbabic            #+#    #+#             */
/*   Updated: 2025/11/09 00:18:59 by zbabic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "error.h"

static bool	is_valid_map_char(char c)
{
	return (c == MAP_EMPTY || c == MAP_WALL || c == MAP_SPACE
		|| c == MAP_PLAYER_NORTH || c == MAP_PLAYER_SOUTH
		|| c == MAP_PLAYER_EAST || c == MAP_PLAYER_WEST);
}

static bool	validate_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (!is_valid_map_char(line[i]))
			return (false);
		i++;
	}
	return (true);
}

static bool	read_map_lines(t_map_line **head, char *first_line, t_env *env)
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
		if (!validate_map_line(line))
			return (free(line), false);
		new_node = create_map_node(line);
		if (!new_node)
			return (free(line), false);
		add_map_line(head, &tail, new_node);
		++(env->map.rows);
		line = get_next_line(env->map.map_file_fd);
	}
	return (true);
}

static int	get_max_line_length(t_map_line *head)
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

static char	*pad_line_with_spaces(char *line, int target_width)
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

static bool	map_list_to_matrix(t_map_line *head, t_env *env)
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
		env->map.matrix[i] = pad_line_with_spaces(current->line, env->map.cols);
		if (!env->map.matrix[i])
			return (false);
		current = current->next;
		++i;
	}
	return (true);
}

void	map_parse_matrix(t_env *env, char *first_line)
{
	t_map_line	*head;

	head = NULL;
	if (!read_map_lines(&head, first_line, env))
		return (free_map_list(&head), error_exit(env,
				ERROR_MSG_MATRIX_READ_FAIL, ERROR_MAP_READ_ERROR));
	if (!head)
		return (error_exit(env, ERROR_MSG_MATRIX_READ_FAIL,
				ERROR_MAP_READ_ERROR));
	env->map.cols = get_max_line_length(head);
	if (!map_list_to_matrix(head, env))
		return (free_map_list(&head), error_exit(env,
				ERROR_MSG_MATRIX_ALLOCATION_FAIL, ERROR_MAP_READ_ERROR));
	free_map_list(&head);
	// TODO: check walls and player
}
