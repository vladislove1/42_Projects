/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmikhajl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 17:45:16 by vmikhajl          #+#    #+#             */
/*   Updated: 2017/10/31 17:45:21 by vmikhajl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		len_of_str(int n)
{
	int		len;
	int		nb;

	nb = n;
	len = 0;
	if (nb < 0)
	{
		nb = -nb;
		len = 1;
	}
	else if (nb == 0)
	{
		len = 1;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

char			*ft_itoa(int n)
{
	char				*str;
	int					nb;
	unsigned int		x;

	x = n;
	str = (char *)malloc(sizeof(char) * (len_of_str(n) + 1));
	if (str == 0)
		return (0);
	nb = 0;
	if (n < 0)
		x = -n;
	if (x == 0)
		str[nb++] = '0';
	while (x > 0)
	{
		str[nb++] = (x % 10) + '0';
		x = x / 10;
	}
	if (n < 0)
		str[nb++] = '-';
	str[nb] = '\0';
	ft_strrev(str);
	return (str);
}
