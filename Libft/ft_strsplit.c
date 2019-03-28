/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmikhajl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 15:28:44 by vmikhajl          #+#    #+#             */
/*   Updated: 2017/11/02 15:28:45 by vmikhajl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static const char	*ft_find_next(const char *str, char c, int skip)
{
	if (skip)
		while (*str != '\0' && *str == c)
			str++;
	else
		while (*str != '\0' && *str != c)
			str++;
	return (str);
}

static int			ft_count_splits(const char *str, char seps)
{
	int i;

	i = 0;
	while (*str != '\0')
	{
		str = ft_find_next(str, seps, 1);
		if (*str != '\0')
		{
			i++;
			str = ft_find_next(str, seps, 0);
		}
	}
	return (i);
}

static char			**ft_delete(char **ret, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		free(ret[i]);
		i++;
	}
	free(ret);
	return (0);
}

char				**ft_strsplit(char const *s, char c)
{
	char		**ret;
	int			i;
	const char	*next;

	if (s == 0)
		return (0);
	ret = (char**)malloc(sizeof(char*) * (ft_count_splits(s, c) + 1));
	if (ret == 0)
		return (0);
	i = 0;
	while (*s != '\0')
	{
		s = ft_find_next(s, c, 1);
		if (*s != '\0')
		{
			next = ft_find_next(s, c, 0);
			ret[i] = ft_strsub(s, 0, next - s);
			if (ret[i] == 0)
				return (ft_delete(ret, i));
			i++;
			s = next;
		}
	}
	ret[i] = 0;
	return (ret);
}
