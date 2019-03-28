/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvikhrov <yvikhrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 16:34:18 by yvikhrov          #+#    #+#             */
/*   Updated: 2017/11/02 21:41:41 by yvikhrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_array_of_strings(char **strings)
{
	char **tmp;

	tmp = strings;
	while (*strings)
	{
		free(*strings);
		strings++;
	}
	free(tmp);
}

char	**ft_strsplit(char const *s, char c, int *size)
{
	char	**str;
	size_t	i;
	size_t	k;

	if (!s)
		return (NULL);
	i = 0;
	k = 0;
	*size = ft_count_words(s, c);
	if ((str = (char**)malloc(sizeof(char*) * (*size + 1))))
	{
		while ((int)i < *size)
		{
			str[i] = ft_count_symbols(&s[k], c);
			while (s[k] == c && s[k])
				k++;
			while (s[k] != c && s[k])
				k++;
			i++;
		}
		str[*size] = NULL;
		return (str);
	}
	return (NULL);
}
