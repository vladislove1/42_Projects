/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmikhajl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 16:27:43 by vmikhajl          #+#    #+#             */
/*   Updated: 2017/10/26 16:27:44 by vmikhajl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcat(char *destination, const char *append)
{
	int		i;
	int		j;
	int		k;

	j = 0;
	i = 0;
	k = 0;
	while (destination[i] != '\0')
	{
		i++;
		k = i;
	}
	if (destination[i] == '\0')
	{
		while (append[j])
			destination[k++] = append[j++];
		destination[k] = '\0';
	}
	return (destination);
}
