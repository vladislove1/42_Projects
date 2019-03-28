/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmikhajl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 18:24:04 by vmikhajl          #+#    #+#             */
/*   Updated: 2018/05/12 18:24:05 by vmikhajl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_mandelbrot(t_mlx *mlx, t_init c)
{
	c.a = 0;
	c.b = 0;
	c.aa = 0;
	c.bb = 0;
	c.ca = 0;
	c.cb = 0;
	c.x = 0;
	c.y = 0;
	c.i = 0;
	draw1(mlx, c);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->image->img, 0, 0);
}

void	draw1(t_mlx *mlx, t_init c)
{
	while (c.y < HEIGHT)
	{
		c.x = 0;
		while (c.x < WIDTH)
		{
			c.a = 1.5 * (c.x - WIDTH / 2) / (0.5 * c.zoom * WIDTH) + c.movex;
			c.b = (c.y - HEIGHT / 2) / (0.5 * c.zoom * HEIGHT) + c.movey;
			c.aa = 0;
			c.bb = 0;
			c.i = -1;
			while (c.i++ < c.maxiter)
			{
				c.ca = c.aa;
				c.cb = c.bb;
				c.aa = c.ca * c.ca - c.cb * c.cb + c.a;
				c.bb = 2 * c.ca * c.cb + c.b;
				fill_rgb(mlx, c.i);
				if ((c.aa * c.aa + c.bb * c.bb) > 4)
					break ;
			}
			pixel_put(mlx->image, c.x, c.y, mlx);
			c.x++;
		}
		c.y++;
	}
}
