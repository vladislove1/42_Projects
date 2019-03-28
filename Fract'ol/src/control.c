/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmikhajl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 18:54:51 by vmikhajl          #+#    #+#             */
/*   Updated: 2018/05/14 18:54:53 by vmikhajl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		position_control(int key, t_mlx *mlx)
{
	int		sign;

	sign = 1;
	if (key == 126 || key == 123)
		sign = -1;
	if (key == 126 || key == 125)
	{
		mlx->init.movey += 10 / (mlx->init.zoom * 20) * sign;
		if (sign == 1)
			ft_putstr("Cam up\n");
		else
			ft_putstr("Cam down\n");
	}
	if (key == 123 || key == 124)
	{
		mlx->init.movex += 10 / (mlx->init.zoom * 20) * sign;
		if (sign == 1)
			ft_putstr("Cam to the left\n");
		else
			ft_putstr("Cam to the right\n");
	}
	update_img(mlx);
}

void		color_control(int key, t_mlx *mlx)
{
	int		flag;

	flag = 0;
	if (key == 18 && mlx->init.col != 1)
	{
		mlx->init.col = 1;
		ft_putstr("color 1\n");
		flag = 1;
	}
	if (key == 19 && mlx->init.col != 2)
	{
		mlx->init.col = 2;
		ft_putstr("color 2\n");
		flag = 1;
	}
	if (key == 20 && mlx->init.col != 3)
	{
		mlx->init.col = 3;
		ft_putstr("color 3\n");
		flag = 1;
	}
	if (flag == 1)
		update_img(mlx);
}

void		zoom_control(int key, t_mlx *mlx)
{
	int		sign;

	sign = 1;
	if (key == 78)
		sign = -1;
	if (key == 69)
	{
		mlx->init.zoom *= 1.1;
		ft_putstr("Zoom +\n");
	}
	if (key == 78)
	{
		mlx->init.zoom /= 1.1;
		ft_putstr("Zoom -\n");
	}
	if (key == 15)
		control(&mlx->init);
	update_img(mlx);
	if (key == 49 && mlx->julia_mouse == 1)
	{
		mlx->julia_mouse = 0;
		key = 0;
	}
	if (key == 49 && mlx->julia_mouse == 0)
		mlx->julia_mouse = 1;
}

void		control(t_init *c)
{
	c->zoom = 0.8;
	c->maxiter = 10;
	c->movex = -0.5;
	c->movey = 0;
	c->a = -0.7;
	c->b = 0.27015;
	c->col = 1;
}

void		fill_rgb(t_mlx *mlx, int i)
{
	if (mlx->init.col == 1)
	{
		mlx->r = 0;
		mlx->g = 0;
		if ((i * 20 % 255) < 50)
			mlx->b = 50;
		else
			mlx->b = i * 20 % 255;
	}
	else if (mlx->init.col == 2)
	{
		mlx->r = (i * 40) & 0xff;
		mlx->g = (i * 20) & 0xff;
		mlx->b = (i * 10) & 0xff;
	}
	else if (mlx->init.col == 3)
		color3(mlx, i);
}
