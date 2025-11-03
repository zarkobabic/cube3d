/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:54:56 by zbabic            #+#    #+#             */
/*   Updated: 2025/05/11 22:14:18 by zbabic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

long	ft_strchr_index(const char *s, int c)
{
	size_t	counter;
	char	converted_char;

	if (s == NULL)
		return (-1);
	converted_char = (char)c;
	counter = 0;
	if (converted_char == 0)
		return (ft_strlen(s));
	else
	{
		while (s[counter] != '\0')
		{
			if (s[counter] == converted_char)
				return (counter);
			++counter;
		}
		return (-1);
	}
}
