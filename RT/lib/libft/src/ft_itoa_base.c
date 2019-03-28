/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvikhrov <yvikhrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 15:44:43 by yvikhrov          #+#    #+#             */
/*   Updated: 2017/11/05 13:45:34 by yvikhrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_base(int num, int base)
{
	long long int	n;
	char			*s;
	char			*basa;
	int				size;

	n = (long long int)num;
	basa = "0123456789ABCDEF";
	size = ft_get_size(n, base);
	if ((s = (char*)malloc(size + 1)))
	{
		s[size] = '\0';
		if (n < 0)
			n = -n;
		while (size)
		{
			s[size - 1] = basa[n % base];
			if (base == 10 && num < 0)
				s[0] = '-';
			n /= base;
			size--;
		}
		return (s);
	}
	return (NULL);
}
