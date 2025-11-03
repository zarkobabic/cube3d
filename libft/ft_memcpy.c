/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 00:49:18 by zbabic            #+#    #+#             */
/*   Updated: 2025/03/17 17:12:54 by zbabic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	counter;

	if (dst == src)
		return (dst);
	counter = 0;
	while (counter < n)
	{
		((char *)dst)[counter] = ((char *)src)[counter];
		counter++;
	}
	return (dst);
}

// #include <stdio.h>
// #include <string.h>
// int main()
// {
// 	// char niz[10] = "1234567890";
// 	// char niz2[5];
// 	//printf("%s", memcpy(niz2, niz, 4));
// 	printf("%s", memcpy(0, 0, 4));
// 	return (0);
// }