/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvikhrov <yvikhrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 18:16:33 by yvikhrov          #+#    #+#             */
/*   Updated: 2018/07/15 18:19:00 by yvikhrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>

double	ft_atod(char *s)
{
	int		int_part;
	int		frac_part;
	double	res;

	frac_part = 0;
	int_part = modif_atoi(s, &s);
	if (*s == '.')
	{
		s++;
		frac_part = ft_atoi(s);
	}
	res = int_part + (double)frac_part / pow(10.0, ft_get_size(frac_part, 10));
	return (res);
}

int		is_floating_point(char *s)
{
	int i;
	int num_dots;

	i = 0;
	num_dots = 0;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i])
	{
		if (s[i] == '.')
		{
			if (++num_dots > 1)
				return (0);
		}
		else if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}
