/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 00:28:58 by zbabic            #+#    #+#             */
/*   Updated: 2025/03/17 17:12:23 by zbabic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	counter;
	char	*string_to_write_to;

	string_to_write_to = (char *)s;
	counter = n;
	while (counter > 0)
	{
		*string_to_write_to = 0;
		string_to_write_to++;
		--counter;
	}
}
