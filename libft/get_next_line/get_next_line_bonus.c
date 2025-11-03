/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:55:41 by zbabic            #+#    #+#             */
/*   Updated: 2025/05/13 06:57:52 by zbabic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <unistd.h>

static size_t	f_line_len(char *head, long endl_index, t_list *buffers_list,
		int read_res)
{
	size_t	line_len;

	if (read_res == 3)
		return (endl_index + 1);
	line_len = ft_strlen(head);
	while (buffers_list && buffers_list->next)
	{
		line_len += BUFFER_SIZE;
		buffers_list = buffers_list->next;
	}
	if (buffers_list)
	{
		if (read_res == 2)
			line_len += ft_strlen(buffers_list->content);
		else if (read_res == 1)
			line_len += endl_index + 1;
	}
	return (line_len);
}

static t_list	*f_populate_line(char **ret_line, char *head,
		t_list *buffers_list, int read_res)
{
	size_t	counter;
	size_t	i;

	i = 0;
	counter = 0;
	while (head[counter] != '\0' && head[counter] != '\n')
		(*ret_line)[i++] = head[counter++];
	if (read_res == 3)
		return ((*ret_line)[i] = '\n', NULL);
	while (buffers_list && buffers_list->next)
	{
		counter = 0;
		while (((char *)(buffers_list->content))[counter] != '\0')
			(*ret_line)[i++] = ((char *)(buffers_list->content))[counter++];
		buffers_list = buffers_list->next;
	}
	counter = 0;
	while (buffers_list && ((char *)(buffers_list->content))[counter] != '\0')
	{
		(*ret_line)[i++] = ((char *)(buffers_list->content))[counter];
		if (((char *)(buffers_list->content))[counter] == '\n')
			return (buffers_list);
		counter++;
	}
	return (buffers_list);
}

static char	*f_handle_endl(char *head, long endl_index, t_list *buffers_list,
		int read_res)
{
	char	*ret_line;
	t_list	*last_node;
	long	i;
	long	new_size;

	new_size = f_line_len(head, endl_index, buffers_list, read_res);
	if (new_size == 0)
		return (NULL);
	ret_line = (char *)malloc((new_size + 1));
	if (!ret_line)
		return (NULL);
	ret_line[new_size] = '\0';
	last_node = f_populate_line(&ret_line, head, buffers_list, read_res);
	i = 0;
	if (read_res == 3)
	{
		while (head[++endl_index] != '\0')
			head[i++] = head[endl_index];
	}
	else if (last_node && endl_index != -1)
	{
		while (((char *)(last_node->content))[++endl_index] != '\0')
			head[i++] = ((char *)(last_node->content))[endl_index];
	}
	return (head[i] = '\0', ret_line);
}

static int	f_read_and_process(int fd, t_list **buffer_list, long *endl_index)
{
	char	*line_buffer;
	int		num_read;
	t_list	*new_node;

	line_buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!line_buffer)
		return (-1);
	num_read = read(fd, line_buffer, BUFFER_SIZE);
	if (num_read < 0)
		return (free(line_buffer), -1);
	else if (num_read == 0)
		return (free(line_buffer), 2);
	line_buffer[num_read] = '\0';
	new_node = ft_lstnew(line_buffer);
	if (!new_node)
		return (free(line_buffer), -1);
	ft_lstadd_back(buffer_list, new_node);
	*endl_index = ft_strchr_index(line_buffer, '\n');
	if (*endl_index != -1)
		return (1);
	else if (num_read < BUFFER_SIZE)
		return (2);
	return (0);
}

/// @brief Reads and returns next line (line until \n 
/// character including it), and returns it in a newly allocated string
/// @param fd file descriptor to read from
/// @return FAIL: NULL if an error occured or we 
/// finished reading from file (EOF)
///
/// SUCCESS: Allocated next line in a new string
char	*get_next_line(int fd)
{
	static char	head[2048][BUFFER_SIZE + 1];
	char		*res;
	long		endl_index;
	t_list		*buffers_list;
	int			read_res;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 2048)
		return (NULL);
	if (head[fd][0] != '\0')
	{
		endl_index = ft_strchr_index(head[fd], '\n');
		if (endl_index > -1)
			return (f_handle_endl(head[fd], endl_index, NULL, 3));
	}
	buffers_list = NULL;
	read_res = 0;
	while (read_res == 0)
		read_res = f_read_and_process(fd, &buffers_list, &endl_index);
	if (read_res == -1)
		return (head[fd][0] = '\0', ft_lstclear(&buffers_list, free), NULL);
	res = f_handle_endl(head[fd], endl_index, buffers_list, read_res);
	if (read_res == 2 && res == NULL)
		head[fd][0] = '\0';
	ft_lstclear(&buffers_list, free);
	return (res);
}
