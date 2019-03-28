/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmikhajl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 17:48:58 by vmikhajl          #+#    #+#             */
/*   Updated: 2017/10/25 17:49:01 by vmikhajl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *destination, const void *source, size_t n)
{
	size_t			i;
	char			*dest;
	char			*sour;

	i = 0;
	sour = (char *)source;
	dest = (char *)destination;
	while (i < n)
	{
		dest[i] = sour[i];
		i++;
	}
	return (destination);
}
