/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 21:22:53 by zbabic            #+#    #+#             */
/*   Updated: 2025/03/17 17:13:05 by zbabic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putendl_fd(char *s, int fd)
{
	size_t	counter;

	counter = 0;
	while (s[counter])
	{
		write(fd, &s[counter], 1);
		++counter;
	}
	write(fd, "\n", 1);
}
