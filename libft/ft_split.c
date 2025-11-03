/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:00:11 by zbabic            #+#    #+#             */
/*   Updated: 2025/03/17 17:13:14 by zbabic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	f_find_word_count(char const *s, char c)
{
	size_t	cnt;
	size_t	word_cnt;
	int		flag;

	flag = 0;
	cnt = 0;
	word_cnt = 0;
	while (s[cnt] && s[cnt] == c)
		++cnt;
	while (s[cnt])
	{
		if (s[cnt] == c && flag == 1)
		{
			++word_cnt;
			flag = 0;
		}
		if (s[cnt] != c)
			flag = 1;
		cnt++;
	}
	if (flag == 1)
		++word_cnt;
	return (word_cnt);
}

static char	*f_allocate_one_word(char const *s, size_t starting_letter,
		size_t size)
{
	char	*word;
	size_t	temp;

	temp = 0;
	word = (char *)malloc((size + 1) * sizeof(char));
	if (!word)
		return (NULL);
	word[size] = '\0';
	while (temp < size)
	{
		word[temp] = s[starting_letter + temp];
		temp++;
	}
	return (word);
}

static char	**f_deallocate_all(char **res_array, size_t res_counter)
{
	size_t	cnt;

	cnt = 0;
	while (cnt < res_counter)
	{
		free(res_array[cnt]);
		++cnt;
	}
	free(res_array);
	return (NULL);
}

static char	**f_split_and_populate(char const *s, char c, char **res_array)
{
	size_t	cnt;
	size_t	res_counter;
	size_t	starting_letter;

	cnt = 0;
	res_counter = 0;
	while (s[cnt] && s[cnt] == c)
		++cnt;
	starting_letter = cnt;
	while (s[cnt])
	{
		while (s[cnt] && s[cnt] != c)
			cnt++;
		res_array[res_counter] = f_allocate_one_word(s, starting_letter, cnt
				- starting_letter);
		if (!(res_array[res_counter]))
			return (f_deallocate_all(res_array, res_counter));
		++res_counter;
		while (s[cnt] && s[cnt] == c)
			cnt++;
		starting_letter = cnt;
	}
	return (res_array);
}

char	**ft_split(char const *s, char c)
{
	size_t	word_count;
	char	**res_array;

	word_count = f_find_word_count(s, c);
	res_array = (char **)malloc((word_count + 1) * sizeof(char *));
	if (!res_array)
		return (NULL);
	res_array[word_count] = NULL;
	return (f_split_and_populate(s, c, res_array));
}

// #include <stdio.h>
// int main()
// {
// 	char	*p = malloc(1);
// 	*p = 0;
// 	char **nizic = ft_split(p, '\0');
// 	int counter = 0;
// 	while(nizic && nizic[counter]){
// 		printf("%s", nizic[counter]);
// 		printf("||\n");
// 		counter++;
// 	};
// 	return (0);
// }