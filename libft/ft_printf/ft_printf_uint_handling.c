/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_uint_handling.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 15:44:42 by zbabic            #+#    #+#             */
/*   Updated: 2025/04/20 17:50:39 by zbabic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	f_calc_num_char_for_uint(unsigned int num, size_t base)
{
	size_t	counter;

	if (num == 0)
		return (1);
	counter = 0;
	while (num > 0)
	{
		++counter;
		num = num / base;
	}
	return (counter);
}

static int	ft_print_uint_base(unsigned int number, char *base,
		unsigned int base_size)
{
	unsigned char	digit;

	digit = base[number % base_size];
	if (number < base_size)
	{
		if (ft_putchar_fd_fail_safe(digit, 1) == -1)
			return (-1);
		else
			return (0);
	}
	if (ft_print_uint_base(number / base_size, base, base_size) == -1)
		return (-1);
	return (ft_putchar_fd_fail_safe(digit, 1));
}

int	ft_put_uint_base(unsigned int nbr, char *base)
{
	unsigned int	base_size;

	if (nbr == 0)
	{
		if (ft_putnbr_fd_fail_safe(0, 1) == -1)
			return (-1);
		else
			return (0);
	}
	base_size = ft_strlen(base);
	return (ft_print_uint_base(nbr, base, base_size));
}

int	handle_u(va_list args, size_t *num_char)
{
	unsigned int	temp_uint;

	temp_uint = va_arg(args, unsigned int);
	*num_char += f_calc_num_char_for_uint(temp_uint, 10);
	return (ft_put_uint_base(temp_uint, "0123456789"));
}

int	handle_hex(va_list args, size_t *num_char, int uppercase)
{
	unsigned int	temp_uint;

	temp_uint = va_arg(args, unsigned int);
	*num_char += f_calc_num_char_for_uint(temp_uint, 16);
	if (uppercase == 1)
		return (ft_put_uint_base(temp_uint, "0123456789ABCDEF"));
	else
		return (ft_put_uint_base(temp_uint, "0123456789abcdef"));
}
