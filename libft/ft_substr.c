/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 22:12:24 by zbabic            #+#    #+#             */
/*   Updated: 2025/03/17 17:14:00 by zbabic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*allocated_mem;
	size_t	size;
	size_t	size_to_allocate;

	size = ft_strlen(s);
	if (start >= size)
		size_to_allocate = 0;
	else if (size - start < len)
		size_to_allocate = size - start;
	else
		size_to_allocate = len;
	allocated_mem = (char *)malloc((size_to_allocate + 1) * sizeof(char));
	if (allocated_mem)
	{
		ft_memcpy(allocated_mem, s + start, size_to_allocate);
		allocated_mem[size_to_allocate] = '\0';
		return (allocated_mem);
	}
	else
		return (NULL);
}
