/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 19:24:51 by zbabic            #+#    #+#             */
/*   Updated: 2025/03/17 17:13:44 by zbabic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	counter;

	counter = 0;
	while (s1[counter] != '\0' && s2[counter] != '\0' && counter < n)
	{
		if (s1[counter] != s2[counter])
			return ((unsigned char)s1[counter] - (unsigned char)s2[counter]);
		counter++;
	}
	if (counter == n)
		return (0);
	else
		return ((unsigned char)s1[counter] - (unsigned char)s2[counter]);
}
