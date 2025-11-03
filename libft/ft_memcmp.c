/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 18:46:34 by zbabic            #+#    #+#             */
/*   Updated: 2025/03/17 17:12:49 by zbabic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	counter;

	counter = 0;
	if (n == 0 || s1 == s2)
		return (0);
	while (counter < n)
	{
		if (((const unsigned char *)s1)[counter]
			!= ((const unsigned char *)s2)[counter])
			return (((const unsigned char *)s1)[counter]
				- ((const unsigned char *)s2)[counter]);
		++counter;
	}
	return (0);
}
