/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmikhajl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 16:12:43 by vmikhajl          #+#    #+#             */
/*   Updated: 2018/01/24 16:29:18 by vmikhajl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		die(char *reason)
{
	ft_putendl(reason);
	return (0);
}

void	rotate_x(t_point **pos, double alpha, t_mlx *mlx)
{
	int		i;
	int		j;

	j = 0;
	while (j < mlx->index)
	{
		i = 0;
		while (i < mlx->width)
		{
			pos[j][i].y = pos[j][i].y - (mlx->control.zoom) / 4 - 20;
			pos[j][i].y = pos[j][i].y * cos(alpha) + pos[j][i].z * sin(alpha);
			pos[j][i].z = pos[j][i].y * -sin(alpha) + pos[j][i].z * cos(alpha);
			i++;
		}
		j++;
	}
}

void	rotate_y(t_point **pos, double alpha, t_mlx *mlx)
{
	int		i;
	int		j;

	j = 0;
	while (j < mlx->index)
	{
		i = 0;
		while (i < mlx->width)
		{
			pos[j][i].x = pos[j][i].x - (mlx->control.zoom) / 2;
			pos[j][i].x = pos[j][i].x * cos(alpha) + pos[j][i].z * sin(alpha);
			pos[j][i].z = -pos[j][i].x * sin(alpha) + pos[j][i].z * cos(alpha);
			i++;
		}
		j++;
	}
}

void	rotate(t_mlx *mlx)
{
	rotate_x(mlx->point, mlx->control.alpha_x, mlx);
	rotate_y(mlx->point, mlx->control.alpha_y, mlx);
	render(mlx, mlx->point);
}

int		main(int argc, char **argv)
{
	t_mlx	*mlx;
	int		fd;

	if (argc != 2)
		return (die("error: invalid count ofarguments\n"
		"usage: ./fdf <arg.fdf>"));
	fd = open(argv[1], O_RDONLY);
	if ((mlx = init(ft_strjoin("FdF - ", argv[1]))) == NULL)
		return (die("error: mlx couldn't init"));
	if (fd < 0 || !read_file(fd, mlx))
		return (die("error: invalid file"));
	rotate(mlx);
	mlx_string_put(mlx->mlx, mlx->win, 20, 10, 0xFFFFFF, "Press '2'");
	mlx_hook(mlx->win, 2, 5, deal_key, mlx);
	mlx_hook(mlx->win, 17, 1L << 17, exit_x, "Exit\n");
	mlx_loop(mlx->mlx);
	return (0);
}
