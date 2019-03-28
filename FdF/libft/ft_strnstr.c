/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmikhajl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 20:44:07 by vmikhajl          #+#    #+#             */
/*   Updated: 2017/10/26 20:44:08 by vmikhajl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str_b, const char *str_a, size_t n)
{
	size_t i;
	size_t j;

	if (*str_a == '\0')
		return ((char *)str_b);
	i = 0;
	while (str_b[i] && i < n)
	{
		j = 0;
		while (str_b[i + j] && i + j < n && str_a[j]
		&& str_b[i + j] == str_a[j])
			j++;
		if (str_a[j] == '\0')
			return ((char *)(str_b + i));
		i++;
	}
	return (NULL);
}
