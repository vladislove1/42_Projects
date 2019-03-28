/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvikhrov <yvikhrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 18:42:11 by yvikhrov          #+#    #+#             */
/*   Updated: 2018/02/04 13:36:20 by yvikhrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s;

	if (s1 && s2 && (s = (char*)malloc(ft_strlen(s1) + ft_strlen(s2) + 1)))
	{
		ft_strcpy(s, (char*)s1);
		free((void*)s1);
		ft_strcat(s, (char*)s2);
		return (s);
	}
	return (NULL);
}
