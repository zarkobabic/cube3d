/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_libft_utilities_for_printf.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:16:58 by zbabic            #+#    #+#             */
/*   Updated: 2025/04/20 18:15:18 by zbabic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include <unistd.h>

/// @brief Write character to the file descriptor given
/// @param c INT Nnumber to print
/// @param fd File descriptor to print to
/// @return SUCCESS: 1 (number of chracter writen)
///
///			FAIL: -1
int	ft_putchar_fd_fail_safe(char c, int fd)
{
	return (write(fd, &c, 1));
}

/// @brief Write number to the file descriptor given
/// @param n INT Nnumber to print
/// @param fd File descriptor to print to
/// @return SUCCESS: 1
///
///			FAIL: -1
static int	f_putnbr_fd_recursive(long num, int fd)
{
	char	char_digit;
	int		digit;

	if (num < 10)
	{
		char_digit = '0' + num;
		if (ft_putchar_fd_fail_safe(char_digit, fd) == -1)
			return (-1);
		return (0);
	}
	else
	{
		digit = num % 10;
		char_digit = '0' + digit;
		if (f_putnbr_fd_recursive(num / 10, fd) == -1)
			return (-1);
		return (ft_putchar_fd_fail_safe(char_digit, fd));
	}
}

/// @brief Write number to the file descriptor given
/// @param n INT Nnumber to print
/// @param fd File descriptor to print to
/// @return SUCCESS: Number of characters writen
///
///			FAIL: -1
int	ft_putnbr_fd_fail_safe(int n, int fd)
{
	long	num;

	num = n;
	if (num < 0)
	{
		if (ft_putchar_fd_fail_safe('-', 1) == -1)
			return (-1);
		num = -num;
	}
	return (f_putnbr_fd_recursive(num, fd));
}

/// @brief Write string to the file descriptor given
/// @param s String to print
/// @param fd File descriptor to print to
/// @return SUCCESS: Number of characters writen
///
///			FAIL: -1
int	ft_putstr_fd_fail_safe(char *s, int fd)
{
	size_t	counter;

	counter = 0;
	while (s[counter])
	{
		if (ft_putchar_fd_fail_safe(s[counter], fd) == -1)
			return (-1);
		++counter;
	}
	return (counter);
}
