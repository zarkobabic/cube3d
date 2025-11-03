/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:28:22 by zbabic            #+#    #+#             */
/*   Updated: 2025/03/17 17:13:32 by zbabic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	counter;

	src_len = ft_strlen(src);
	counter = 0;
	if (dstsize > 0)
	{
		while (src[counter] != '\0' && counter < dstsize - 1)
		{
			dst[counter] = src[counter];
			++counter;
		}
		dst[counter] = '\0';
	}
	return (src_len);
}
