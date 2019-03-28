/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvikhrov <yvikhrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 13:03:50 by yvikhrov          #+#    #+#             */
/*   Updated: 2017/10/29 15:16:22 by yvikhrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	c_char;
	char	*str;

	i = 0;
	str = (char*)s;
	c_char = (char)c;
	if (c_char == '\0')
		return (&str[ft_strlen(s)]);
	while (str[i] && str[i] != c_char)
		i++;
	if (str[i] != c_char)
		return (NULL);
	return (&str[i]);
}
