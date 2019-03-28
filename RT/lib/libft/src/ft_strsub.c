/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvikhrov <yvikhrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 18:11:14 by yvikhrov          #+#    #+#             */
/*   Updated: 2017/11/05 13:59:30 by yvikhrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int beg, unsigned int n)
{
	char			*str;
	unsigned int	i;
	size_t			len_s;

	i = 0;
	len_s = ft_strlen(s);
	if (s && len_s >= n && (str = (char*)malloc(n + 1)))
	{
		while (i < n && s[beg + i])
		{
			str[i] = s[beg + i];
			i++;
		}
		str[i] = '\0';
		return (str);
	}
	return (NULL);
}
