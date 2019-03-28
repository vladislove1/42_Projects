/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmikhajl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 18:30:27 by vmikhajl          #+#    #+#             */
/*   Updated: 2017/10/25 18:30:28 by vmikhajl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *destination, const void *source, int c, size_t n)
{
	unsigned char	*dest;
	unsigned char	*sour;

	sour = (unsigned char *)source;
	dest = (unsigned char *)destination;
	while (n > 0 && *sour != (unsigned char)c)
	{
		n--;
		*dest++ = *sour++;
	}
	if (n > 0)
	{
		*dest++ = *sour++;
		return ((void *)dest);
	}
	else
		return (0);
}
