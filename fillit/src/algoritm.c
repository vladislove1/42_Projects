/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algoritm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmikhajl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 20:00:47 by vmikhajl          #+#    #+#             */
/*   Updated: 2017/12/01 20:00:49 by vmikhajl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

t_tetrim	find_free(char **map, int *s, int size)
{
	t_tetrim	pos;

	pos.y = -1;
	pos.x = -1;
	while (map[*s / size])
	{
		if (map[*s / size][*s % size] == '.')
		{
			pos.y = *s / size;
			pos.x = *s % size;
			return (pos);
		}
		(*s)++;
	}
	return (pos);
}

int			find_solution(t_list *lst, char **map, int side)
{
	int			skip;

	skip = 0;
	if (lst->next == NULL)
		return (1);
	while (place(map, lst, side, &skip))
	{
		if (find_solution(lst->next, map, side))
			return (1);
		else
		{
			tet_delete(map, lst);
			skip++;
		}
	}
	return (0);
}

char		**create_map(int *side, t_fillit *main)
{
	int			count;
	char		**map;
	int			i;
	int			j;

	map = NULL;
	count = main->count_t;
	if (count * 4 > *side * *side)
		while (count * 4 > *side * *side)
			*side += 1;
	map = (char **)malloc(sizeof(char *) * *side + 1);
	i = 0;
	while (i <= *side)
	{
		map[i] = (char *)malloc(sizeof(char) * *side + 1);
		j = 0;
		while (j < *side)
			map[i][j++] = '.';
		map[i][*side] = '\0';
		j = 0;
		i++;
	}
	map[*side] = NULL;
	return (map);
}

void		algoritm(t_list *lst, t_fillit *main)
{
	char		**map;
	int			side;

	side = 2;
	map = create_map(&side, main);
	while (!(find_solution(lst, map, side)))
	{
		freemap(map, side);
		side++;
		map = create_map(&side, main);
	}
	print(map);
}
