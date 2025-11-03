/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 00:31:42 by zbabic            #+#    #+#             */
/*   Updated: 2025/03/17 02:08:42 by zbabic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static t_list	*f_make_new_node(void *content, void (*del)(void *))
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
	{
		del(content);
		return (NULL);
	}
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_head;
	t_list	*new_tail;
	t_list	*new_node;

	new_head = NULL;
	while (lst)
	{
		new_node = f_make_new_node(f(lst->content), del);
		if (!new_node)
		{
			ft_lstclear(&new_head, del);
			return (NULL);
		}
		if (!new_head)
			new_head = new_node;
		else
			new_tail->next = new_node;
		new_tail = new_node;
		lst = lst->next;
	}
	return (new_head);
}
