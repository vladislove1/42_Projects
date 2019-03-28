/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmikhajl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 15:08:43 by vmikhajl          #+#    #+#             */
/*   Updated: 2018/03/16 15:08:45 by vmikhajl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		clear(t_mlx *mlx, int y, char *line)
{
	int			i;
	t_list		*next;

	i = 0;
	if (y == 0)
	{
		while (i < mlx->index)
			free(mlx->point[i++]);
		free(mlx->point);
	}
	if (y == 1)
		free(line);
	while (mlx->lst)
	{
		next = (mlx->lst)->next;
		ft_memdel(&(mlx->lst)->content);
		ft_memdel((void **)mlx->lst);
		mlx->lst = next;
	}
	if (mlx->image->img)
		mlx_destroy_image(mlx->mlx, mlx->image->img);
	return (-1);
}

int		exit_x(char *str)
{
	ft_putstr(str);
	exit(1);
	return (0);
}

void	control(t_mlx *mlx)
{
	mlx->control.alpha_x = 1;
	mlx->control.alpha_y = 0.6;
	mlx->control.alpha_z = 0;
	mlx->control.up = HEIGHT / 3;
	mlx->control.right = (WIDTH) / 2;
	mlx->control.z = 1;
	mlx->control.zoom = (WIDTH + HEIGHT) / 3;
}

int		deal_key(int key, t_mlx *mlx)
{
	if (key == 53)
	{
		ft_putstr("Exit\n");
		exit(1);
	}
	if (key == 126 || key == 125 || key == 124 || key == 123)
		position_control(key, mlx);
	if (key == 6 || key == 7)
		z_control(key, mlx);
	if (key == 83 || key == 84 || key == 86 || key == 87)
		rotate_control(key, mlx);
	if (key == 69 || key == 78)
		zoom_control(key, mlx);
	if (key == 18 || key == 19)
		projection_control(mlx, key);
	return (0);
}
