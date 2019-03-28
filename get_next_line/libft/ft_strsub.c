/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmikhajl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 18:56:58 by vmikhajl          #+#    #+#             */
/*   Updated: 2017/10/29 18:56:59 by vmikhajl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	size_t	i;

	if (s == 0)
		return (0);
	substring = ft_strnew(len);
	if (substring == 0)
		return (0);
	s = s + start;
	i = 0;
	while (i < len)
	{
		substring[i] = s[i];
		i++;
	}
	return (substring);
}
