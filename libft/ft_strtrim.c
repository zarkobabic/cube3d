/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 00:39:01 by zbabic            #+#    #+#             */
/*   Updated: 2025/03/17 17:13:57 by zbabic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	f_calculate_new_size(char const *s1, char const *set)
{
	size_t	cnt;
	size_t	seq_counter;
	size_t	new_size;

	new_size = 0;
	cnt = 0;
	seq_counter = 0;
	while (s1[cnt] && ft_strchr(set, s1[cnt]))
		cnt++;
	while (s1[cnt])
	{
		if (ft_strchr(set, s1[cnt]))
			++seq_counter;
		else
			seq_counter = 0;
		++new_size;
		++cnt;
	}
	new_size -= seq_counter;
	return (new_size);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*allocated_mem;
	size_t	cnt;
	size_t	seq_counter;
	size_t	new_size;

	new_size = f_calculate_new_size(s1, set);
	allocated_mem = (char *)malloc((new_size + 1) * sizeof(char));
	if (!allocated_mem)
		return (NULL);
	cnt = 0;
	seq_counter = 0;
	while (s1[cnt] && ft_strchr(set, s1[cnt]))
		cnt++;
	while (new_size > 0)
	{
		allocated_mem[seq_counter] = s1[cnt];
		--new_size;
		++seq_counter;
		++cnt;
	}
	allocated_mem[seq_counter] = '\0';
	return (allocated_mem);
}

// #include <stdio.h>
// int main()
// {
// 	char *s1 = "   \t  \n\n \t\t  \n\n\nHello \t
//Please\n Trim me !\n   \n \n \t\t\n  ";
// 	char *ret = ft_strtrim(s1, " \n\t");
// 	printf("%s", ret);
// 	return (0);
// }