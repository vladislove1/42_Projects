/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmikhajl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 18:24:16 by vmikhajl          #+#    #+#             */
/*   Updated: 2018/05/12 18:24:17 by vmikhajl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	update_julia(t_mlx *mlx, t_init c)
{
	c.aa = 0;
	c.bb = 0;
	c.ca = 0;
	c.cb = 0;
	c.movex += 0.5;
	c.i = 0;
	mlx_destroy_image(mlx->mlx, mlx->image->img);
	mlx->image->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	mlx->image->ptr = mlx_get_data_addr(mlx->image->img, &mlx->image->bpp,
		&mlx->image->size, &mlx->image->endian);
	mlx->image->bpp /= 8;
	draw(mlx, c);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->image->img, 0, 0);
	mlx_string_put(mlx->mlx, mlx->win, 20, 10, 0xFF, "zoom   - key + or -");
	mlx_string_put(mlx->mlx, mlx->win, 20, 30, 0xFF, "iter   - key * or /");
	mlx_string_put(mlx->mlx, mlx->win, 20, 50, 0xFF, "color  - key 1"
	" or 2 or 3");
	mlx_string_put(mlx->mlx, mlx->win, 20, 70, 0xFF, "reset  - key R");
	mlx_string_put(mlx->mlx, mlx->win, 20, 750, 0xFF, "enable/disable mouse"
	" control - press space");
}

int		mouse_julia(int x, int y, t_mlx *mlx)
{
	if (mlx->fractal == 1 && mlx->julia_mouse == 1)
	{
		mlx->init.a = x * 2;
		mlx->init.b = y * 2 - 800;
		update_julia(mlx, mlx->init);
	}
	return (0);
}

void	init_julia(t_mlx *mlx, t_init c)
{
	c.aa = 0;
	c.bb = 0;
	c.ca = 0;
	c.cb = 0;
	c.movex += 0.5;
	c.i = 0;
	draw(mlx, c);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->image->img, 0, 0);
}

void	draw(t_mlx *mlx, t_init c)
{
	c.y = 0;
	while (c.y < HEIGHT)
	{
		c.x = 0;
		while (c.x < WIDTH)
		{
			c.aa = 1.5 * (c.x - WIDTH / 2) / (0.5 * c.zoom * WIDTH) + c.movex;
			c.bb = (c.y - HEIGHT / 2) / (0.5 * c.zoom * HEIGHT) + c.movey;
			c.i = 0;
			while (c.i < c.maxiter)
			{
				c.ca = c.aa;
				c.cb = c.bb;
				c.aa = c.ca * c.ca - c.cb * c.cb - 0.8 + (c.a / WIDTH);
				c.bb = 2 * c.ca * c.cb + c.b / WIDTH;
				fill_rgb(mlx, c.i);
				if ((c.aa * c.aa + c.bb * c.bb) > 4)
					break ;
				c.i++;
			}
			pixel_put(mlx->image, c.x, c.y, mlx);
			c.x++;
		}
		c.y++;
	}
}
