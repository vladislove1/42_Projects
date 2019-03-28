/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmikhajl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 15:57:52 by vmikhajl          #+#    #+#             */
/*   Updated: 2018/04/19 16:00:57 by vmikhajl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include "libft.h"
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include "mlx.h"
# define WIDTH 1000
# define HEIGHT 800

typedef struct		s_init
{
	double		a;
	double		b;
	double		aa;
	double		bb;
	double		ca;
	double		cb;
	double		zoom;
	int			maxiter;
	int			x;
	int			y;
	int			i;
	double		movex;
	double		movey;
	int			col;
}					t_init;

typedef struct		s_image
{
	void		*img;
	char		*ptr;
	int			bpp;
	int			size;
	int			endian;
}					t_image;

typedef struct		s_mlx
{
	int			fractal;
	int			julia_mouse;
	void		*mlx;
	void		*win;
	int			r;
	int			g;
	int			b;
	t_image		*image;
	t_init		init;
}					t_mlx;

t_mlx				*init(char *title);
void				draw(t_mlx *mlx, t_init c);
void				draw1(t_mlx *mlx, t_init c);
void				draw2(t_mlx *mlx, t_init c);
void				draw3(t_mlx *mlx, t_init c);
void				update_img(t_mlx *mlx);
void				fractal_init(t_mlx *mlx);
int					hook_mousedown(int button, int x, int y, t_mlx *mlx);
int					hook_mouseup(int button, int x, int y, t_mlx *mlx);
void				init_mandelbrot(t_mlx *mlx, t_init c);
void				init_julia(t_mlx *mlx, t_init c);
void				init_burn_s(t_mlx *mlx, t_init c);
void				fill_rgb(t_mlx *mlx, int i);
void				pixel_put(t_image *image, int x, int y, t_mlx *mlx);
int					deal_key(int key, t_mlx *mlx);
int					exit_x(char *str);
void				control(t_init *c);
int					mouse_julia(int x, int y, t_mlx *mlx);
void				position_control(int key, t_mlx *mlx);
void				color_control(int key, t_mlx *mlx);
void				init_newton(t_mlx *mlx, t_init c);
void				zoom_control(int key, t_mlx *mlx);
void				zoom(int x, int y, t_mlx *mlx);
void				dezoom(t_mlx *mlx);
int					mouse_hook(int mousecode, int x, int y, t_mlx *mlx);
void				color3(t_mlx *mlx, int i);
#endif
