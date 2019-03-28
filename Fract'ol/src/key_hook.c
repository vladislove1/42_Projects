/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmikhajl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 19:59:39 by vmikhajl          #+#    #+#             */
/*   Updated: 2018/05/12 19:59:41 by vmikhajl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	iter_control(int key, t_mlx *mlx)
{
	int		sign;

	sign = 1;
	if (key == 75)
		sign = -1;
	if (key == 67)
	{
		if (mlx->init.maxiter > 9)
			mlx->init.maxiter += 10 * sign;
		else
			mlx->init.maxiter += 1 * sign;
	}
	if (key == 75 && mlx->init.maxiter > 0)
	{
		if (mlx->init.maxiter > 20)
			mlx->init.maxiter += 10 * sign;
		else
			mlx->init.maxiter += 1 * sign;
	}
	update_img(mlx);
}

int		deal_key(int key, t_mlx *mlx)
{
	if (key == 53)
	{
		exit(1);
	}
	if (key == 75 || key == 67)
		iter_control(key, mlx);
	if (key == 69 || key == 78 || key == 15 || key == 49)
		zoom_control(key, mlx);
	if (key == 16)
	{
		mlx->init.maxiter = mlx->init.maxiter + 100;
		update_img(mlx);
	}
	if (key == 126 || key == 125 || key == 124 || key == 123)
		position_control(key, mlx);
	if (key == 18 || key == 19 || key == 20)
		color_control(key, mlx);
	return (0);
}

int		exit_x(char *str)
{
	ft_putstr(str);
	exit(1);
	return (0);
}
