/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvikhrov <yvikhrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 13:30:27 by yvikhrov          #+#    #+#             */
/*   Updated: 2017/10/29 15:17:49 by yvikhrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	size_t	k;
	char	*b;
	char	*l;

	k = 0;
	b = (char*)big;
	l = (char*)little;
	if (l[k] == '\0')
		return (b);
	while (b[k])
	{
		if (!ft_memcmp((const void*)&b[k], (const void*)l, ft_strlen(little)))
			return (&b[k]);
		k++;
	}
	return (NULL);
}
