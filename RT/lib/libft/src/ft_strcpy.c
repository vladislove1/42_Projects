/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvikhrov <yvikhrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 19:43:21 by yvikhrov          #+#    #+#             */
/*   Updated: 2017/10/29 19:11:09 by yvikhrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcpy(char *dst, const char *src)
{
	char	*s;
	char	*begin;

	begin = dst;
	s = (char*)src;
	while ((*dst = *s))
	{
		dst++;
		s++;
	}
	return (begin);
}
