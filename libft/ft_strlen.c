/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:41:44 by zbabic            #+#    #+#             */
/*   Updated: 2025/08/03 23:18:17 by zbabic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	counter;

	counter = 0;
	if (!s)
		return (0);
	while (s[counter] != '\0')
	{
		++counter;
	}
	return (counter);
}
// #include <stdio.h>
// int main(void)
// {
// 	printf("%zu",ft_strlen(""));
// 	return (0);
// }