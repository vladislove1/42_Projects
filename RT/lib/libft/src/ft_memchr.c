/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvikhrov <yvikhrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 18:39:03 by yvikhrov          #+#    #+#             */
/*   Updated: 2017/10/29 14:43:20 by yvikhrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	size_t			i;
	unsigned char	c_char;

	str = (unsigned char*)s;
	c_char = (unsigned char)c;
	i = 0;
	while (i < n && str[i] != c_char)
		i++;
	if (i == n)
		return (NULL);
	return ((void*)&str[i]);
}
