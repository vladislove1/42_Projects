/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetrim_arr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmikhajl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 18:58:59 by vmikhajl          #+#    #+#             */
/*   Updated: 2017/11/30 18:59:09 by vmikhajl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	freemap(char **map, int side)
{
	int		i;

	i = 0;
	while (i != side - 1)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	tet_delete(char **map, t_list *lst)
{
	int count;

	count = 0;
	while (count != 4)
	{
		map[lst->place[count].y][lst->place[count].x] = '.';
		count++;
	}
}

void	delete_arr(char **arr, t_fillit *a)
{
	int		i;

	i = 0;
	while (i < a->count_t)
	{
		free(arr[i]);
		i++;
	}
	i = 0;
	free(arr);
}

char	**ft_conv(char **arr, int fd)
{
	char	buf[1];
	int		a;
	int		b;
	int		lines;

	a = 0;
	while ((read(fd, buf, 1)))
	{
		b = 0;
		lines = 0;
		while (lines != 4)
		{
			if (*buf == '\n')
				lines++;
			else
			{
				arr[a][b] = *buf;
				b++;
			}
			read(fd, buf, 1);
		}
		arr[a][b] = '\0';
		a++;
	}
	return (arr);
}

char	**create_arr(char *file, t_fillit *a)
{
	char	**arr;
	int		fd;
	int		i;

	i = 0;
	arr = (char **)malloc(sizeof(char *) * a->count_t);
	if (!arr)
		return (0);
	while (i < a->count_t)
	{
		arr[i] = (char *)malloc(sizeof(char) * 17);
		i++;
	}
	fd = open(file, O_RDONLY);
	arr = ft_conv(arr, fd);
	close(fd);
	return (arr);
}
