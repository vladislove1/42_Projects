/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvikhrov <yvikhrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 16:35:51 by yvikhrov          #+#    #+#             */
/*   Updated: 2017/11/01 17:54:34 by yvikhrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*str;
	size_t	i;
	size_t	k;

	i = 0;
	k = 0;
	if (s && (str = (char*)malloc(ft_strlen(s) + 1)) && f)
	{
		while (s[i])
		{
			if ((str[k] = f(s[i])))
				k++;
			i++;
		}
		str[i] = '\0';
		return (str);
	}
	return (NULL);
}
