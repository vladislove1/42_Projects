/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmikhajl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 16:52:44 by vmikhajl          #+#    #+#             */
/*   Updated: 2017/10/26 16:52:46 by vmikhajl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *destination, const char *append, size_t n)
{
	int		i;
	size_t	j;
	int		k;

	j = 0;
	i = 0;
	k = 0;
	while (destination[i] != '\0')
	{
		i++;
		k = i;
	}
	if (destination[i] == '\0')
	{
		while (append[j] != '\0' && j != n)
			destination[k++] = append[j++];
		destination[k] = '\0';
	}
	return (destination);
}
