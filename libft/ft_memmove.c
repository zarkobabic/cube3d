/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:43:37 by zbabic            #+#    #+#             */
/*   Updated: 2025/03/17 17:12:57 by zbabic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	counter;

	counter = 0;
	if (dst == src || len == 0)
		return (dst);
	if (src < dst)
	{
		counter = len - 1;
		while (counter > 0)
		{
			((char *)dst)[counter] = ((char *)src)[counter];
			--counter;
		}
		((char *)dst)[0] = ((char *)src)[0];
	}
	else
	{
		counter = 0;
		while (counter < len)
		{
			((char *)dst)[counter] = ((char *)src)[counter];
			++counter;
		}
	}
	return (dst);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char	niz[10] = "1234567890";
//
// 	//overlap end of src beginning of dst
// 	// memmove(&niz[2], &niz[1], 2);
// 	ft_memmove(&niz[2], &niz[1], 2);
//	
// 	//overlap end of dst beginning of src
// 	//memmove(&niz[1], &niz[2], 2);
// 	//ft_memmove(&niz[1], &niz[2], 2);
//
// 	printf("%s", niz);
// 	printf("\n");
// 	return (0);
// }
