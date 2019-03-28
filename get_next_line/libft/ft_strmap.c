/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmikhajl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 18:13:38 by vmikhajl          #+#    #+#             */
/*   Updated: 2017/10/29 18:13:39 by vmikhajl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char			*temp;
	unsigned int	i;

	if (s == NULL || f == NULL)
		return (NULL);
	i = 0;
	temp = ft_strnew(ft_strlen(s));
	if (temp == 0)
		return (0);
	while (s[i])
	{
		temp[i] = (*f)(s[i]);
		i++;
	}
	return (temp);
}
