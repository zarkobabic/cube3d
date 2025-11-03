/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_text_handling.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 15:35:25 by zbabic            #+#    #+#             */
/*   Updated: 2025/04/20 17:50:19 by zbabic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_c(va_list args, size_t *num_char)
{
	char	temp_char;

	temp_char = va_arg(args, int);
	*num_char += 1;
	return (ft_putchar_fd_fail_safe(temp_char, 1));
}

int	handle_s(va_list args, size_t *num_char)
{
	char	*temp_str;

	temp_str = va_arg(args, char *);
	if (temp_str)
	{
		*num_char += ft_strlen(temp_str);
		return (ft_putstr_fd_fail_safe(temp_str, 1));
	}
	else
	{
		*num_char += 6;
		return (ft_putstr_fd_fail_safe("(null)", 1));
	}
}
