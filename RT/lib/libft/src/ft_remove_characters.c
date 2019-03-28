/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_characters.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvikhrov <yvikhrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 15:49:56 by yvikhrov          #+#    #+#             */
/*   Updated: 2018/07/15 18:23:01 by yvikhrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_remove_characters(char *str, char *chars)
{
	int		i;
	int		k;
	char	*new_str;
	int		symb_count;

	i = -1;
	k = 0;
	symb_count = 0;
	while (str[++i])
	{
		if (!ft_strchr(chars, str[i]))
			symb_count++;
	}
	new_str = (char*)malloc(symb_count + 1);
	i = -1;
	while (str[++i])
	{
		if (!ft_strchr(chars, str[i]))
		{
			new_str[k] = str[i];
			k++;
		}
	}
	new_str[symb_count] = '\0';
	return (new_str);
}
