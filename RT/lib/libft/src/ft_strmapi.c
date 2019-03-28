/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvikhrov <yvikhrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 17:54:52 by yvikhrov          #+#    #+#             */
/*   Updated: 2017/11/01 17:56:59 by yvikhrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str;
	unsigned int	i;
	unsigned int	k;

	i = 0;
	k = 0;
	if (s && (str = (char*)malloc(ft_strlen(s) + 1)) && f)
	{
		while (s[i])
		{
			if ((str[k] = f(k, s[i])))
				k++;
			i++;
		}
		str[i] = '\0';
		return (str);
	}
	return (NULL);
}
