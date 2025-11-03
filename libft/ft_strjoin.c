/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 22:48:31 by zbabic            #+#    #+#             */
/*   Updated: 2025/03/17 17:13:25 by zbabic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*allocated_mem;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	allocated_mem = (char *)malloc((s1_len + s2_len + 1) * sizeof(char));
	if (allocated_mem)
	{
		ft_memcpy(allocated_mem, s1, s1_len);
		ft_memcpy(allocated_mem + s1_len, s2, s2_len);
		allocated_mem[s1_len + s2_len] = '\0';
		return (allocated_mem);
	}
	else
	{
		return (NULL);
	}
}
