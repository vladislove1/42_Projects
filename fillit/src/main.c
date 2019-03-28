/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmikhajl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 18:54:32 by vmikhajl          #+#    #+#             */
/*   Updated: 2017/11/17 18:54:34 by vmikhajl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	print(char **map)
{
	int			i;

	i = 0;
	while (map[i] != NULL)
	{
		ft_putstr(map[i]);
		ft_putstr("\n");
		i++;
	}
}

int		memory_list(t_fillit *main)
{
	t_list		*list;
	int			i;

	i = 1;
	list = main->list;
	list->tetrimin[0].x = 0;
	list->next = NULL;
	while (i < main->count_t + 1)
	{
		list->next = (t_list *)malloc(sizeof(t_list));
		if (list->next == NULL)
			return (0);
		else
		{
			list = list->next;
			list->next = NULL;
		}
		i++;
	}
	return (1);
}

void	create_list2(char **tetriminos, t_list *list, int i, int j)
{
	int			block;
	int			line;

	line = 0;
	block = 0;
	while (tetriminos[i][j])
	{
		if (j >= 4 && (j % 4) == 0)
			line++;
		if (tetriminos[i][j] == '#')
		{
			list->tetrimin[block].y = line;
			list->tetrimin[block].x = j % 4;
			block++;
		}
		j++;
	}
}

void	create_list(char **tetriminos, t_fillit *main)
{
	int			i;
	int			j;
	t_list		*list;
	t_list		*lst;

	i = 0;
	lst = main->list;
	list = main->list;
	while (i < main->count_t)
	{
		j = 0;
		create_list2(tetriminos, list, i, j);
		list->num = i;
		list->l = 'A' + i;
		list = list->next;
		i++;
	}
	algoritm(lst, main);
}

int		main(int argc, char **argv)
{
	char		**tetr_arr;
	t_fillit	*fillit;

	fillit = malloc(sizeof(t_fillit));
	if (!fillit)
		return (0);
	if (argc == 2)
	{
		if (check_open(argv[1], fillit))
		{
			tetr_arr = create_arr(argv[1], fillit);
			if (validate(tetr_arr, fillit) && memory_list(fillit))
				create_list(tetr_arr, fillit);
			else
				ft_putstr("error\n");
			if (tetr_arr)
				delete_arr(tetr_arr, fillit);
		}
		else
			ft_putstr("error\n");
	}
	else
		ft_putstr("usage: ./fillit \"argument\"\n");
	return (0);
}
