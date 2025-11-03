/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 17:43:58 by zbabic            #+#    #+#             */
/*   Updated: 2025/03/17 17:12:28 by zbabic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	f_calculate_size(int n)
{
	long	num;
	int		size;

	if (n == 0)
		return (1);
	num = n;
	if (num < 0)
		num = -num;
	size = 0;
	while (num > 0)
	{
		++size;
		num = num / 10;
	}
	return (size);
}

static void	f_itoa_fill_recursive(long number, int index, char *res)
{
	int	digit;

	digit = 0;
	if (number < 10)
		res[index] = '0' + number;
	else
	{
		digit = number % 10;
		f_itoa_fill_recursive(number / 10, index - 1, res);
		res[index] = '0' + digit;
	}
}

char	*ft_itoa(int n)
{
	int		size;
	char	*res;
	int		negative;
	long	num;

	num = n;
	negative = 0;
	size = f_calculate_size(n);
	if (num < 0)
	{
		++size;
		negative = 1;
		num = -num;
	}
	res = (char *)malloc((size + 1) * sizeof(char));
	if (!res)
		return (NULL);
	res[size] = 0;
	if (negative)
		res[0] = '-';
	f_itoa_fill_recursive(num, size - 1, res);
	return (res);
}

// #include <stdio.h>
// int main()
// {
// 	printf("%s", ft_itoa(-456123));
// 	return (0);
// }