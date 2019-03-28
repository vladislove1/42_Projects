/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmikhajl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 21:27:05 by vmikhajl          #+#    #+#             */
/*   Updated: 2018/04/01 21:27:06 by vmikhajl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	projection_control(t_mlx *mlx, int key)
{
	if (key == 18)
	{
		mlx->control.alpha_x = 0;
		mlx->control.alpha_y = 0;
		mlx->control.alpha_z = 0;
		mlx->control.up = HEIGHT / 3;
		mlx->control.right = (WIDTH) / 2;
		mlx->control.z = 1;
		mlx->control.zoom = (WIDTH + HEIGHT) / 3;
	}
	if (key == 19)
		control(mlx);
	ft_putstr("Change of projection\n");
	update_img(mlx);
}

void	rotate_control(int key, t_mlx *mlx)
{
	int		sign;

	sign = 1;
	if (key == 86 || key == 87 || key == 88)
		sign = -1;
	if (key == 83 || key == 86)
	{
		mlx->control.alpha_x = mlx->control.alpha_x + (3.14 / 36) * sign;
		if (mlx->control.alpha_x > 3.14 * 2
			&& mlx->control.alpha_x > -(3.14 * 2))
			mlx->control.alpha_x = 0;
		ft_putstr("Rotate  x\n");
	}
	if (key == 84 || key == 87)
	{
		mlx->control.alpha_y = mlx->control.alpha_y
		+ (3.14 / 36) * sign;
		if (mlx->control.alpha_y > 3.14 * 2
		&& mlx->control.alpha_y > -(3.14 * 2))
			mlx->control.alpha_y = 0;
		ft_putstr("Rotate  y\n");
	}
	update_img(mlx);
}

void	z_control(int key, t_mlx *mlx)
{
	int		sign;

	sign = 1;
	if (key == 6)
		sign = -1;
	mlx->control.z = mlx->control.z + (1 * sign);
	update_img(mlx);
}

void	position_control(int key, t_mlx *mlx)
{
	int		sign;

	sign = 1;
	if (key == 125 || key == 124)
		sign = -1;
	if (key == 126 || key == 125)
	{
		mlx->control.up = mlx->control.up + 100 * sign;
		if (sign == 1)
			ft_putstr("Cam up\n");
		else
			ft_putstr("Cam down\n");
	}
	if (key == 123 || key == 124)
	{
		mlx->control.right = mlx->control.right + 100 * sign;
		if (sign == 1)
			ft_putstr("Cam to the left\n");
		else
			ft_putstr("Cam to the right\n");
	}
	update_img(mlx);
}

void	zoom_control(int key, t_mlx *mlx)
{
	int		sign;

	sign = 1;
	if (key == 78)
		sign = -1;
	if (key == 69 && mlx->control.zoom < 8000)
	{
		mlx->control.zoom = mlx->control.zoom + (200);
		ft_putstr("Zoom +\n");
	}
	if (key == 78 && mlx->control.zoom > 400)
	{
		mlx->control.zoom = mlx->control.zoom - (200);
		ft_putstr("Zoom -\n");
	}
	update_img(mlx);
}
