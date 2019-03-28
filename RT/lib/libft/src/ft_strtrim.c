/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvikhrov <yvikhrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 18:55:47 by yvikhrov          #+#    #+#             */
/*   Updated: 2017/11/02 16:31:41 by yvikhrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*str;
	size_t	i;
	size_t	len;

	i = 0;
	if (s)
	{
		while (ft_isspace(*s))
			s++;
		if (!(len = ft_strlen(s)))
			return (ft_strdup(""));
		while (ft_isspace(s[len - 1]))
			len--;
		if ((str = (char*)malloc(len + 1)))
		{
			str[len] = '\0';
			while (i < len)
			{
				str[i] = s[i];
				i++;
			}
			return (str);
		}
	}
	return (NULL);
}
