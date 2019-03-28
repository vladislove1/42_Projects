/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmikhajl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 22:12:12 by vmikhajl          #+#    #+#             */
/*   Updated: 2017/12/01 22:12:13 by vmikhajl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int			place(char **map, t_list *lst, int side, int *skip)
{
	t_tetrim	point;
	t_tetrim	g_next;
	int			count;

	count = 0;
	g_next = lst->tetrimin[0];
	point = place_v2(map, lst, side, skip);
	if (point.x == -1)
		return (0);
	while (count != 4)
	{
		map[point.y + g_next.y - lst->tetrimin[0].y][point.x +
			g_next.x - lst->tetrimin[0].x] = lst->l;
		lst->place[count].y = point.y + g_next.y - lst->tetrimin[0].y;
		lst->place[count].x = point.x + g_next.x - lst->tetrimin[0].x;
		count++;
		g_next = lst->tetrimin[count];
	}
	return (1);
}

int			can_place(char **map, int side, t_list *lst, t_tetrim point)
{
	int			count;
	t_tetrim	pos;

	count = 0;
	pos = lst->tetrimin[0];
	while (count != 4)
	{
		if (((pos.y + point.y - lst->tetrimin[0].y) > (side - 1))
		|| ((pos.x + point.x - lst->tetrimin[0].x) > (side - 1)))
			return (0);
		if (map[point.y + pos.y - lst->tetrimin[0].y][point.x +
			pos.x - lst->tetrimin[0].x] != '.')
			return (0);
		count++;
		pos = lst->tetrimin[count];
	}
	return (1);
}

t_tetrim	place_v2(char **map, t_list *lst, int side, int *skip)
{
	t_tetrim	point;

	point = find_free(map, skip, side);
	if (point.x == -1)
		return (point);
	if (!(can_place(map, side, lst, point)))
	{
		while (point.x > -1)
		{
			if (can_place(map, side, lst, point))
				break ;
			++(*skip);
			point = find_free(map, skip, side);
		}
	}
	return (point);
}
