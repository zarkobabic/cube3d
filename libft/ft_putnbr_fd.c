/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 21:38:00 by zbabic            #+#    #+#             */
/*   Updated: 2025/03/15 22:33:41 by zbabic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static void	f_putnbr_fd_recursive(long num, int fd)
{
	char	char_digit;
	int		digit;

	if (num < 10)
	{
		char_digit = '0' + num;
		write(fd, &char_digit, 1);
	}
	else
	{
		digit = num % 10;
		char_digit = '0' + digit;
		f_putnbr_fd_recursive(num / 10, fd);
		write(fd, &char_digit, 1);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	long	num;

	num = n;
	if (num < 0)
	{
		write(fd, "-", 1);
		num = -num;
	}
	f_putnbr_fd_recursive(num, fd);
}
