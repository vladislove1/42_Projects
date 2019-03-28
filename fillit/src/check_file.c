/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmikhajl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 16:11:53 by vmikhajl          #+#    #+#             */
/*   Updated: 2017/11/23 16:11:55 by vmikhajl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char const *s)
{
	int		i;

	i = 0;
	if (s)
	{
		while (s[i] != '\0')
			ft_putchar(s[i++]);
	}
}

char	check_file2(int fd, char *temp, t_fillit *a)
{
	a->lines++;
	if (read(fd, temp, 1))
		a->count_ch++;
	if (a->chars != 4 || ((*temp == '\n') && (a->lines != 4))
		|| (*temp != '#' && *temp != '.' && *temp != '\n'))
		return (0);
	a->chars = 0;
	if (a->lines == 4 && *temp == '\n')
	{
		a->lines = 0;
		a->count_t++;
	}
	if (*temp == '#' || *temp == '.')
	{
		a->chars++;
	}
	return (*temp);
}

int		check_file(int fd, char *temp, t_fillit *a)
{
	while (a->count_ch++ < 545 && read(fd, temp, 1))
	{
		if (*temp != '#' && *temp != '.' && *temp != '\n')
			return (0);
		if (*temp == '#' || *temp == '.')
			a->chars++;
		else
			*temp = check_file2(fd, temp, a);
	}
	a->count_ch--;
	return (*temp == '\n' && (a->count_ch == 20 ||
		((a->count_ch + 1) % 21) == 0)) ? (1) : (0);
}

int		check_open(char *file, t_fillit *a)
{
	int		fd;
	char	temp[1];

	a->lines = 0;
	a->chars = 0;
	a->count_t = 0;
	a->count_ch = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (0);
	return (check_file(fd, temp, a));
}
