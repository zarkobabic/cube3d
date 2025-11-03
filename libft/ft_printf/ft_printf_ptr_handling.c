/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ptr_handling.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 15:50:03 by zbabic            #+#    #+#             */
/*   Updated: 2025/04/20 17:39:08 by zbabic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

int	handle_p(va_list args, size_t *num_char)
{
	int	ret_value;

	ret_value = ft_put_pointer_fd(va_arg(args, void *), 1);
	if (ret_value == -1)
		return (-1);
	else
	{
		*num_char += ret_value;
		return (0);
	}
}
