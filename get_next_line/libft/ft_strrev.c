/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmikhajl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 20:29:31 by vmikhajl          #+#    #+#             */
/*   Updated: 2017/11/08 20:29:39 by vmikhajl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strrev(char *str)
{
	char	*str_end;
	char	c;

	if (str == NULL)
		return ;
	str_end = str + ft_strlen(str) - 1;
	while (str < str_end)
	{
		c = *str;
		*str++ = *str_end;
		*str_end-- = c;
	}
}
