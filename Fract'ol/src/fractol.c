/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmikhajl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 16:02:29 by vmikhajl          #+#    #+#             */
/*   Updated: 2018/04/19 16:02:30 by vmikhajl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		die(char *reason)
{
	ft_putendl(reason);
	return (0);
}

void	update_img(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->image->img);
	mlx->image->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	mlx->image->ptr = mlx_get_data_addr(mlx->image->img, &mlx->image->bpp,
		&mlx->image->size, &mlx->image->endian);
	mlx->image->bpp /= 8;
	if (mlx->fractal == 0)
		init_mandelbrot(mlx, mlx->init);
	else if (mlx->fractal == 1)
		init_julia(mlx, mlx->init);
	else if (mlx->fractal == 2)
		init_burn_s(mlx, mlx->init);
	else if (mlx->fractal == 3)
		init_newton(mlx, mlx->init);
	mlx_string_put(mlx->mlx, mlx->win, 20, 10, 0xFF, "zoom   - key + or -");
	mlx_string_put(mlx->mlx, mlx->win, 20, 30, 0xFF, "iter   - key * or /");
	mlx_string_put(mlx->mlx, mlx->win, 20, 50, 0xFF, "color  - key 1 or 2"
	" or 3");
	mlx_string_put(mlx->mlx, mlx->win, 20, 70, 0xFF, "reset  - key R");
	if (mlx->fractal == 1)
		mlx_string_put(mlx->mlx, mlx->win, 20, 750, 0xFF, "enable/disable mouse"
			" control - press space");
}

void	pixel_put(t_image *image, int x, int y, t_mlx *mlx)
{
	int			i;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	i = image->bpp * (x + y * WIDTH);
	image->ptr[i] = mlx->b;
	image->ptr[++i] = mlx->g;
	image->ptr[++i] = mlx->r;
}

int		fract_comp(char **av, t_mlx *mlx)
{
	if (ft_strcmp(av[1], "mandelbrot") == 0)
		mlx->fractal = 0;
	else if (ft_strcmp(av[1], "julia") == 0)
		mlx->fractal = 1;
	else if (ft_strcmp(av[1], "burningship") == 0)
		mlx->fractal = 2;
	else if (ft_strcmp(av[1], "tricorn") == 0)
		mlx->fractal = 3;
	else
	{
		ft_putendl("Usage: ./fractol \"mandelbrot\", \"julia\", "
			"\"burningship\", \"tricorn\"");
		return (0);
	}
	return (1);
}

int		main(int argc, char **argv)
{
	t_mlx		*mlx;
	int			flag;

	flag = 0;
	if (argc != 2)
		return (die("error: invalid count ofarguments\n"
		"Usage: ./fractol <name>"
		"\nExample : julia | mandelbrot | burningship | tricorn"));
	if ((mlx = init(ft_strjoin("Fractal - ", argv[1]))) == NULL)
		return (die("error: mlx couldn't init"));
	control(&mlx->init);
	if ((fract_comp(argv, mlx)) == 0)
		return (0);
	fractal_init(mlx);
	mlx->julia_mouse = 1;
	mlx_hook(mlx->win, 2, 5, deal_key, mlx);
	mlx_hook(mlx->win, 6, 1L < 6, mouse_julia, mlx);
	mlx_string_put(mlx->mlx, mlx->win, 20, 10, 0xFF, "Press '2'");
	mlx_mouse_hook(mlx->win, mouse_hook, mlx);
	mlx_hook(mlx->win, 17, 1L << 17, exit_x, "Exit\n");
	mlx_loop(mlx->mlx);
	return (0);
}
