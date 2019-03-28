/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvikhrov <yvikhrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 20:18:22 by yvikhrov          #+#    #+#             */
/*   Updated: 2017/10/29 14:18:57 by yvikhrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	str = (char*)s2;
	i = 0;
	j = 0;
	while (s1[i])
		i++;
	while (str[j])
	{
		s1[i + j] = str[j];
		j++;
	}
	s1[i + j] = '\0';
	return (s1);
}
