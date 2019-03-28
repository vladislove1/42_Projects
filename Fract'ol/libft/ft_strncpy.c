/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmikhajl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 16:03:24 by vmikhajl          #+#    #+#             */
/*   Updated: 2017/10/26 16:03:25 by vmikhajl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *destination, const char *source, size_t n)
{
	char	*s2;

	s2 = destination;
	while (*source != '\0' && n > 0)
	{
		*destination++ = *source++;
		n--;
	}
	while (n > 0)
	{
		*destination++ = '\0';
		n--;
	}
	return (s2);
}
