/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 18:51:40 by zbabic            #+#    #+#             */
/*   Updated: 2025/03/17 17:13:41 by zbabic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	size;
	char	*new_string;
	size_t	counter;

	size = ft_strlen(s);
	new_string = (char *)malloc((size + 1) * sizeof(char));
	if (!new_string)
		return (NULL);
	counter = 0;
	while (counter < size)
	{
		new_string[counter] = f(counter, s[counter]);
		counter++;
	}
	new_string[counter] = '\0';
	return (new_string);
}
