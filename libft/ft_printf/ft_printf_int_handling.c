/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_int_handling.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 15:48:19 by zbabic            #+#    #+#             */
/*   Updated: 2025/04/20 17:50:39 by zbabic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	f_calc_num_char_for_int(int number)
{
	long	num;
	size_t	counter;

	if (number == 0)
		return (1);
	num = number;
	counter = 0;
	if (num < 0)
	{
		++counter;
		num = -num;
	}
	while (num > 0)
	{
		++counter;
		num = num / 10;
	}
	return (counter);
}

int	handle_di(va_list args, size_t *num_char)
{
	int	temp_int;

	temp_int = va_arg(args, int);
	*num_char += f_calc_num_char_for_int(temp_int);
	return (ft_putnbr_fd_fail_safe(temp_int, 1));
}
