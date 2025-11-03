/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 23:43:52 by zbabic            #+#    #+#             */
/*   Updated: 2025/05/24 19:13:01 by zbabic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	f_skip_whitespaces(const char *str, size_t *counter)
{
	while (str[*counter] == '\t' || str[*counter] == '\n'
		|| str[*counter] == '\v' || str[*counter] == '\f'
		|| str[*counter] == '\r' || str[*counter] == ' ')
		*counter = *counter + 1;
}

static void	f_skip_signes_and_mark_negative(const char *str, size_t *counter,
		int *negative, int *sign_counter)
{
	while (str[*counter] == '+' || str[*counter] == '-')
	{
		if (str[*counter] == '-')
			*negative = 1;
		*sign_counter = *sign_counter + 1;
		*counter = *counter + 1;
	}
}

/// @brief 
/// @param str 
/// @return Number (type int) that is parsed from the string until
///  the character is different from digit, or until end of the string  
int	ft_atoi(const char *str)
{
	size_t	counter;
	long	res;
	int		negative;
	int		sign_counter;

	sign_counter = 0;
	res = 0;
	counter = 0;
	negative = 0;
	f_skip_whitespaces(str, &counter);
	f_skip_signes_and_mark_negative(str, &counter, &negative, &sign_counter);
	if (sign_counter > 1)
		return (0);
	while (str[counter] >= '0' && str[counter] <= '9')
	{
		res = res * 10 + (str[counter] - '0');
		++counter;
	}
	if (negative == 1)
		res = -res;
	return (res);
}

// #include <stdio.h>
// #include <stdlib.h>

// int	main(void)
// {
// 	printf("%d", ft_atoi("0"));
// 	return (0);
// }