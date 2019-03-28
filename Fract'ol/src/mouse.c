/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmikhajl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 17:19:33 by vmikhajl          #+#    #+#             */
/*   Updated: 2018/05/07 17:19:35 by vmikhajl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	color3(t_mlx *mlx, int i)
{
	mlx->r = 255 & 0xff;
	mlx->g = 255 & 0xff;
	mlx->b = 255 & 0xff;
	if (i >= 9)
	{
		mlx->r = 0 & 0xff;
		mlx->g = 0 & 0xff;
		mlx->b = 0 & 0xff;
	}
}

void	zoom(int x, int y, t_mlx *mlx)
{
	if (x > WIDTH / 2)
		mlx->init.movex += 10 / (mlx->init.zoom * 20) * 0.17;
	else
		mlx->init.movex -= 10 / (mlx->init.zoom * 20) * 0.17;
	if (y > WIDTH / 2)
		mlx->init.movey += 10 / (mlx->init.zoom * 20) * 0.17;
	else
		mlx->init.movey -= 10 / (mlx->init.zoom * 20) * 0.17;
	mlx->init.zoom *= 1.1;
	mlx->init.maxiter++;
}

void	dezoom(t_mlx *mlx)
{
	mlx->init.zoom /= 1.1;
	mlx->init.maxiter--;
}

int		mouse_hook(int mousecode, int x, int y, t_mlx *mlx)
{
	if (mousecode == 4 || mousecode == 1)
		zoom(x, y, mlx);
	else if (mousecode == 5 || mousecode == 2)
		dezoom(mlx);
	update_img(mlx);
	return (0);
}
