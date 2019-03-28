/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmikhajl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 18:42:30 by vmikhajl          #+#    #+#             */
/*   Updated: 2017/10/29 18:42:32 by vmikhajl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
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
		temp[i] = (*f)(i, s[i]);
		i++;
	}
	return (temp);
}
