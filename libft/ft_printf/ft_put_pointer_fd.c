/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_pointer_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:38:19 by zbabic            #+#    #+#             */
/*   Updated: 2025/04/20 18:09:43 by zbabic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_put_pointer_recursive_fd(unsigned long long addr,
										unsigned int counter,
										int fd)
{
	unsigned char	hex_digit;
	unsigned int	hex_digit_int;
	int				temp_counter;

	hex_digit_int = addr % 16;
	if (hex_digit_int >= 10)
		hex_digit = 'a' + (hex_digit_int - 10);
	else
		hex_digit = '0' + hex_digit_int;
	if (addr < 16)
	{
		if (ft_putchar_fd_fail_safe(hex_digit, fd) == -1)
			return (-1);
		return (counter + 1);
	}
	else
	{
		temp_counter = ft_put_pointer_recursive_fd(addr / 16, counter + 1, fd);
		if (temp_counter == -1 || ft_putchar_fd_fail_safe(hex_digit, fd) == -1)
			return (-1);
		return (temp_counter);
	}
}

/// @brief Prints pointer to file descriptor using write function
/// @param ptr Pointer to be printed
/// @param fd File descriptor to write to
/// @return SUCCESS: Number of printed characters 
/// (length of the pointer in character representation)
///
///			FAIL: If write fail in any moment return value is set to -1
int	ft_put_pointer_fd(void *ptr, int fd)
{
	unsigned long long	addr;
	int					ret_value;

	addr = (unsigned long long)ptr;
	if (ft_putstr_fd_fail_safe("0x", fd) == -1)
		return (-1);
	ret_value = ft_put_pointer_recursive_fd(addr, 0, fd);
	if (ret_value == -1)
		return (ret_value);
	else
		return (ret_value + 2);
}
