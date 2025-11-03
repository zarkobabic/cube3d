/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:54:05 by zbabic            #+#    #+#             */
/*   Updated: 2025/03/17 17:12:45 by zbabic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			counter;
	unsigned char	converted_char;

	converted_char = (unsigned char)c;
	counter = 0;
	while (counter < n)
	{
		if (((unsigned char *)s)[counter] == converted_char)
			return ((void *)(s + counter));
		++counter;
	}
	return (NULL);
}
