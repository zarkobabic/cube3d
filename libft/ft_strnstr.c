/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 20:18:42 by zbabic            #+#    #+#             */
/*   Updated: 2025/03/17 17:13:48 by zbabic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*temp;
	size_t	cnt;

	if (*needle == 0)
		return ((char *)haystack);
	temp = (char *)haystack;
	while (*temp)
	{
		cnt = 0;
		if (len < (size_t)(temp - haystack + ft_strlen(needle)))
			return (NULL);
		while (temp[cnt] && needle[cnt] && temp[cnt] == needle[cnt])
			++cnt;
		if (needle[cnt] == '\0')
			return (temp);
		++temp;
	}
	return (NULL);
}

// #include <stdio.h>
// int main()
// {
// 	// char haystack[] = "papadou";
// 	// char needle[] = "padd";
// 	printf("%s", ft_strnstr("", "l", -1));
// 	return (0);
// }