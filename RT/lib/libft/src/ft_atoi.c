/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvikhrov <yvikhrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 16:16:35 by yvikhrov          #+#    #+#             */
/*   Updated: 2017/11/05 13:07:08 by yvikhrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_atoi(const char *s)
{
	unsigned long long	res;
	size_t				i;
	size_t				temp;
	int					count;

	res = 0;
	i = 0;
	count = 0;
	while (ft_isspace(s[i]))
		i++;
	if (s[temp = i] == '-' || s[i] == '+')
		i++;
	while (s[i] >= '0' && s[i] <= '9')
	{
		res = res * 10 + s[i] - '0';
		if (res > 9223372036854775807LL && s[temp] == '-')
			return (0);
		else if (res > 9223372036854775807LL && s[temp] != '-')
			return (-1);
		i++;
	}
	if (s[temp] == '-')
		res = -res;
	return ((int)res);
}

int			modif_atoi(char *s, char **end_nbr)
{
	unsigned long long	res;
	size_t				i;
	size_t				temp;
	int					count;

	res = 0;
	i = 0;
	count = 0;
	while (ft_isspace(s[i]))
		i++;
	if (s[temp = i] == '-' || s[i] == '+')
		i++;
	while (s[i] >= '0' && s[i] <= '9')
	{
		res = res * 10 + s[i] - '0';
		if (res > 9223372036854775807LL && s[temp] == '-')
			return (0);
		else if (res > 9223372036854775807LL && s[temp] != '-')
			return (-1);
		i++;
	}
	if (s[temp] == '-')
		res = -res;
	*end_nbr = s + i;
	return ((int)res);
}

static int	in_base(char c, int base)
{
	int					i;
	static const char	*base_string = "0123456789ABCDEF";

	i = 0;
	while (i < base)
	{
		if (c == base_string[i])
			return (i);
		i++;
	}
	return (-1);
}

char		*ft_strtoupper(char *in)
{
	char	*s;

	s = in;
	while (*in)
	{
		*in = ft_toupper(*in);
		in++;
	}
	return (s);
}

int			ft_atoi_base(char *s, int base)
{
	unsigned long long	res;
	size_t				i;
	size_t				temp;
	int					count;

	res = 0;
	i = 0;
	count = 0;
	ft_strtoupper(s);
	while (ft_isspace(s[i]))
		i++;
	if (s[temp = i] == '-' || s[i] == '+')
		i++;
	while ((count = in_base(s[i], base)) != -1)
	{
		res = res * base + count;
		i++;
	}
	if (s[temp] == '-' && base == 10)
		res = -res;
	return ((int)res);
}
