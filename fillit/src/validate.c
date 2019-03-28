/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knikanor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:06:29 by knikanor          #+#    #+#             */
/*   Updated: 2017/11/23 15:21:24 by knikanor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdio.h>

static	int			is_four(char *row)
{
	int			i;
	int			block;

	i = 0;
	block = 0;
	while (row[i])
	{
		if (row[i] == '#')
			block++;
		i++;
	}
	if (block == 4)
		return (1);
	else
		return (0);
}

static	int			step(char *tetrimino)
{
	int			x;
	int			valid;

	valid = 0;
	x = 0;
	while (x <= 15)
	{
		if (tetrimino[x] == '#')
		{
			if (x <= 11 && tetrimino[x + 1] == '#')
				valid++;
			if (x <= 11 && tetrimino[x + 4] == '#')
				valid++;
			if ((x > 11 && x < 15) && tetrimino[x + 1] == '#')
				valid++;
		}
		x++;
	}
	if (valid != 3 && valid != 4)
		return (0);
	return (1);
}

int					validate(char **tetrimino, t_fillit *a)
{
	int			i;

	i = 0;
	while (i < a->count_t)
	{
		if (!(step(tetrimino[i])) || !(is_four(tetrimino[i])))
			return (0);
		i++;
	}
	i = 0;
	return (1);
}
