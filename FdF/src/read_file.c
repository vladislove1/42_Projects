/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmikhajl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 13:32:34 by vmikhajl          #+#    #+#             */
/*   Updated: 2018/03/24 13:32:35 by vmikhajl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		fill_rgb(t_point *p)
{
	p->r = (p->color >> 16) & 0xff;
	p->g = (p->color >> 8) & 0xff;
	p->b = p->color & 0xff;
}

int			get_pos(char *line, t_point **pos, t_mlx *mlx, int y)
{
	int			i;
	int			j;

	mlx->split = ft_strsplit(line, ' ');
	j = 0;
	i = 0;
	pos[y] = (t_point *)malloc(sizeof(t_point) * mlx->width);
	while (mlx->split[i])
	{
		pos[y][i].x = j;
		pos[y][i].y = mlx->h;
		pos[y][i].z = ft_atoi(mlx->split[i]) * -1;
		pos[y][i].d3z = ft_atoi(mlx->split[i]) * -1;
		if (pos[y][i].d3z != 0)
			pos[y][i].z = pos[y][i].d3z * mlx->control.z;
		if ((pos[y][i].color = check_color(mlx->split[i])) == 0)
			pos[y][i].color = get_color(pos[y][i].z);
		j = j + mlx->step;
		fill_rgb(&pos[y][i]);
		i++;
	}
	while (i > -1)
		free(mlx->split[i--]);
	free(mlx->split);
	return (1);
}

void		get_map(t_mlx *mlx, t_list *lst, t_point **pos)
{
	int			step;
	t_list		*temp;
	int			y;

	y = 0;
	step = 0;
	temp = lst;
	if (mlx->width > mlx->index)
		mlx->step = mlx->control.zoom / mlx->width;
	else
		mlx->step = mlx->control.zoom / mlx->index;
	if (mlx->control.zoom / mlx->index < mlx->step)
		mlx->step = mlx->control.zoom / mlx->index;
	mlx->h = 0;
	while (temp)
	{
		get_pos(temp->content, pos, mlx, y);
		y++;
		mlx->h = mlx->h + mlx->step;
		temp = temp->next;
	}
}

int			get_lines(int fd, t_mlx *mlx, t_list **lst)
{
	char		*line;
	t_list		*list;
	int			ret;
	int			cw;

	cw = -1;
	while ((ret = get_next_line(fd, &line)))
	{
		if (ret == -1)
			return (clear(mlx, 1, line));
		if (cw == -1)
			cw = ft_countwords(line, ' ');
		mlx->width = ft_countwords(line, ' ');
		list = ft_lstnew(line, ft_strlen(line) + 1);
		mlx->index++;
		if (cw != mlx->width)
			return (clear(mlx, 1, line));
		ft_lstadd(lst, list);
		free(line);
	}
	if (mlx->width < 2 || mlx->index < 2)
		return (clear(mlx, 2, line));
	ft_lstrev(lst);
	close(fd);
	return (1);
}

int			read_file(int fd, t_mlx *mlx)
{
	mlx->lst = NULL;
	mlx->index = 0;
	mlx->width = 0;
	control(mlx);
	if (get_lines(fd, mlx, &mlx->lst) == -1)
		return (0);
	if ((mlx->point = (t_point **)malloc(sizeof(t_point **) * mlx->index)))
		get_map(mlx, mlx->lst, mlx->point);
	return (1);
}
