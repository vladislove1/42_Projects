/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmikhajl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 17:08:29 by vmikhajl          #+#    #+#             */
/*   Updated: 2017/10/28 17:08:31 by vmikhajl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static	int		toint(int i, const char *str, int sign)
{
	unsigned	long	int	res;

	res = 0;
	while (str[i] && str[i] >= 48 && str[i] <= 57)
	{
		res = res * 10 + (str[i] - 48);
		i++;
	}
	if (res >= 9223372036854775807 && sign == 1)
		return (-1);
	else if (res > 9223372036854775807 && sign == -1)
		return (0);
	return ((int)res);
}

int				ft_atoi(const char *str)
{
	int						i;
	int						dec;
	int						res;
	int						sign;

	i = 0;
	sign = 1;
	dec = 1;
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
