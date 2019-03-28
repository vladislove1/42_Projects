/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_symbols.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvikhrov <yvikhrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 16:45:52 by yvikhrov          #+#    #+#             */
/*   Updated: 2017/11/02 21:41:03 by yvikhrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_count_symbols(char const *s, char c)
{
	size_t	len;
	size_t	i;
	size_t	k;
	char	*str;

	len = 0;
	i = 0;
	k = 0;
	while (s[i] == c && s[i])
		i++;
	while (s[i] != c && s[i])
	{
		len++;
		i++;
	}
	str = (char*)malloc(len + 1);
	while (k < len)
	{
		str[k] = s[i - len];
		i++;
		k++;
	}
	str[k] = '\0';
	return (str);
}
