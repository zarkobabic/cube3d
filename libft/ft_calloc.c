/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:43:25 by zbabic            #+#    #+#             */
/*   Updated: 2025/04/29 19:35:02 by zbabic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*allocated_mem;

	allocated_mem = malloc(count * size);
	if (allocated_mem)
	{
		ft_bzero(allocated_mem, count * size);
		return (allocated_mem);
	}
	else
		return (NULL);
}
