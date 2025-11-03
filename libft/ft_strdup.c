/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 21:50:01 by zbabic            #+#    #+#             */
/*   Updated: 2025/03/17 17:13:21 by zbabic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	char	*allocated_mem;
	size_t	len;

	len = ft_strlen(s1);
	allocated_mem = (char *)malloc((len + 1) * sizeof(char));
	if (allocated_mem)
	{
		return (ft_memcpy(allocated_mem, s1, len + 1));
	}
	else
		return (NULL);
}
