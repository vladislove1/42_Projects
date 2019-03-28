/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_size.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvikhrov <yvikhrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 17:20:41 by yvikhrov          #+#    #+#             */
/*   Updated: 2017/11/04 17:20:56 by yvikhrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_get_size(long long n, int base)
{
	int				size;

	size = 1;
	if (n < 0)
	{
		if (base == 10)
			size++;
		n = -n;
	}
	while (n >= base)
	{
		n /= base;
		size++;
	}
	return (size);
}
