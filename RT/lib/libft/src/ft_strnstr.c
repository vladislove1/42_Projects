/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvikhrov <yvikhrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 14:40:51 by yvikhrov          #+#    #+#             */
/*   Updated: 2017/11/05 13:56:07 by yvikhrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *b, const char *l, size_t len)
{
	size_t	i;
	size_t	len1;

	len1 = ft_strlen(l);
	i = 0;
	while (*b && ((i + len1) <= len))
	{
		if (!ft_strncmp(b, l, len1))
			return ((char*)b);
		b++;
		i++;
	}
	ft_strncmp(b, l, len1);
	return (NULL);
}
