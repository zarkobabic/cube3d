/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:06:28 by zbabic            #+#    #+#             */
/*   Updated: 2025/03/17 17:13:18 by zbabic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	counter;
	char	converted_char;

	converted_char = (char)c;
	counter = 0;
	if (converted_char == 0)
		return (&(((char *)s)[ft_strlen(s)]));
	else
	{
		while (s[counter] != '\0')
		{
			if (s[counter] == converted_char)
				return (&(((char *)s)[counter]));
			++counter;
		}
		return (NULL);
	}
}

// #include <stdio.h>
// int main()
// {
// 	char m[] = "teste";

// 	printf("%p", ft_strchr(m, '\0'));
// 	return (0);
// }