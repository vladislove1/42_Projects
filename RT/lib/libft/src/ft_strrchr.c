/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvikhrov <yvikhrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 13:28:09 by yvikhrov          #+#    #+#             */
/*   Updated: 2017/10/29 15:16:37 by yvikhrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	c_char;
	char	*str;

	i = ft_strlen(s);
	str = (char*)s;
	c_char = (char)c;
	if (c_char == '\0')
		return (&str[i]);
	while (i-- && str[i] != c_char)
		;
	if (str[i] != c_char)
		return (0);
	return (&str[i]);
}
