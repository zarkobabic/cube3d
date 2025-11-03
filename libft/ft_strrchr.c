/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:59:28 by zbabic            #+#    #+#             */
/*   Updated: 2025/03/17 17:13:52 by zbabic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	counter;
	char	*res;
	char	converted_char;

	converted_char = (char)c;
	res = NULL;
	counter = 0;
	if (converted_char == 0)
		return (&(((char *)s)[ft_strlen(s)]));
	else
	{
		while (s[counter] != '\0')
		{
			if (s[counter] == converted_char)
				res = (&(((char *)s)[counter]));
			++counter;
		}
		return (res);
	}
}
