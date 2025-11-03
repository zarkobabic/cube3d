/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:54:02 by zbabic            #+#    #+#             */
/*   Updated: 2025/03/17 17:13:28 by zbabic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	dst_len;
	size_t	counter;

	counter = 0;
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dstsize == 0 || dstsize <= dst_len)
		return (src_len + dstsize);
	while (src[counter] != '\0' && dst_len + counter < dstsize - 1)
	{
		dst[dst_len + counter] = src[counter];
		++counter;
	}
	dst[dst_len + counter] = '\0';
	return (dst_len + src_len);
}
