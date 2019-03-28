/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmikhajl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 19:05:08 by vmikhajl          #+#    #+#             */
/*   Updated: 2017/10/25 19:05:09 by vmikhajl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *arr, int c, size_t n)
{
	size_t				i;
	unsigned	char	*dest;

	i = 0;
	dest = (unsigned char *)arr;
	while (i < n)
	{
		if (dest[i] == (unsigned char)c)
		{
			return ((void *)(dest + i));
		}
		i++;
	}
	return (0);
}
