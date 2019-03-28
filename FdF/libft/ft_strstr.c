/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmikhajl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 19:45:17 by vmikhajl          #+#    #+#             */
/*   Updated: 2017/10/26 19:45:19 by vmikhajl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strstr(const char *str_b, const char *str_a)
{
	const char *temp1;
	const char *temp2;

	if (*str_a == '\0')
		return ((char*)str_b);
	while (*str_b)
	{
		temp1 = str_b;
		temp2 = str_a;
		while (*temp2 && *temp1 == *temp2)
		{
			temp1++;
			temp2++;
		}
		if (*temp2 == '\0')
			return ((char*)str_b);
		str_b++;
	}
	return (0);
}
