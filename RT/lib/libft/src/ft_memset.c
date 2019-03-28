/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvikhrov <yvikhrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 18:35:21 by yvikhrov          #+#    #+#             */
/*   Updated: 2017/10/29 17:53:05 by yvikhrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*str;
	unsigned char	k;
	size_t			i;

	k = (unsigned char)c;
	i = 0;
	str = (unsigned char*)b;
	while (i < len)
	{
		str[i] = k;
		i++;
	}
	return ((void*)str);
}
