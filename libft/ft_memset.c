/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:08:49 by zbabic            #+#    #+#             */
/*   Updated: 2025/03/17 17:13:01 by zbabic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	counter;
	char	*string_to_write_to;

	string_to_write_to = (char *)b;
	counter = len;
	while (counter > 0)
	{
		*string_to_write_to = c;
		string_to_write_to++;
		--counter;
	}
	return (b);
}

// #include <stdio.h>
// #include <string.h>
// int main(void)
// {
// 	char random_str[4] = "AAAA";
// 	char separator[1] = "\0";
// 	char random_str_std[4] = "AAAA";
// 	char *standard = memset(&random_str, 'U', 2);
// 	char *mine = ft_memset(&random_str_std, 'U', 2);
// 	printf("%s", mine);
// 	printf("%s", separator);
// 	printf("\n");
// 	printf("%s", standard);
// 	printf("\n");
// 	return 0;
// }
