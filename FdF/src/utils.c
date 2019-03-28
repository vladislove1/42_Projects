/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmikhajl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 21:21:17 by vmikhajl          #+#    #+#             */
/*   Updated: 2018/03/30 21:21:18 by vmikhajl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			ft_lstrev(t_list **alst)
{
	t_list					*prev;
	t_list					*cur;
	t_list					*next;

	prev = NULL;
	cur = *alst;
	while (cur != NULL)
	{
		next = cur->next;
		cur->next = prev;
		prev = cur;
		cur = next;
	}
	*alst = prev;
}

int				ft_countwords(char *str, char sep)
{
	int						result;
	int						i;

	i = 0;
	result = 0;
	while (str[i] && str[i] == sep)
		i++;
	while (str[i])
	{
		while (str[i] && str[i] != sep)
			i++;
		result++;
		while (str[i] && str[i] == sep)
			i++;
	}
	return (result);
}

int				get_color(int z)
{
	if (z < 0)
		return (0xFF0000);
	if (z > 0)
		return (0x0000FF);
	return (0x00FF00);
}

int				toint(int i, const char *str, int sign)
{
	unsigned	long	int	res;

	res = 0;
	while ((str[i] && str[i] >= 48 && str[i] <= 57)
	|| (str[i] >= 65 && str[i] <= 122))
	{
		if (str[i] && (str[i] >= 48 && str[i] <= 57))
			res = res * 16 + (str[i] - 48);
		if (str[i] && (str[i] >= 97 && str[i] <= 122))
			res = res * 16 + (str[i] - 87);
		if (str[i] && (str[i] >= 65 && str[i] <= 90))
			res = res * 16 + (str[i] - 55);
		i++;
	}
	if (res >= 9223372036854775807 && sign == 1)
		return (-1);
	else if (res > 9223372036854775807 && sign == -1)
		return (0);
	return ((int)res);
}

int				ft_atoi_x(const char *str)
{
	int						i;
	int						res;
	int						sign;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == '\n' || str[i] == '\t' || str[i] == '\r' || str[i] == '\v'
	|| str[i] == '\f' || str[i] == ' ')
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	res = toint(i, str, sign);
	return (res * sign);
}
