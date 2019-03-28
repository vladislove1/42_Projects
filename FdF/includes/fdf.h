/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmikhajl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 15:53:42 by vmikhajl          #+#    #+#             */
/*   Updated: 2018/03/05 15:53:47 by vmikhajl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "mlx.h"
# include "libft.h"
# include <math.h>
# define WIDTH 1900
# define HEIGHT 1200

typedef struct		s_control
{
	double		alpha_z;
	double		alpha_x;
	double		alpha_y;
	double		up;
	double		right;
	double		z;
	double		zoom;
}					t_control;

typedef struct		s_image
{
	void		*img;
	char		*ptr;
	int			bpp;
	int			size;
	int			endian;
}					t_image;

typedef struct		s_bras
{
	int			dx;
	int			dy;
	int			err;
	int			sx;
	int			sy;
	int			e2;
}					t_bras;

typedef struct		s_point
{
	int			x;
	int			y;
	int			z;
	int			d3z;
	int			color;
	int			r;
	int			g;
	int			b;
}					t_point;

typedef struct		s_mlx
{
	int			step;
	int			index;
	int			width;
	void		*mlx;
	void		*win;
	t_point		**point;
	t_control	control;
	t_list		*lst;
	t_image		*image;
	char		**split;
	int			h;
}					t_mlx;

int					ft_countwords(char *str, char sep);
void				control(t_mlx *mlx);
int					read_file(int fd, t_mlx *mlx);
void				rotate_x(t_point **pos, double alpha, t_mlx *mlx);
void				rotate_y(t_point **pos, double alpha, t_mlx *mlx);
void				rotate_z(t_point **pos, double alpha, t_mlx *mlx);
void				get_map(t_mlx *mlx, t_list *lst, t_point **pos);
int					deal_key(int key, t_mlx *mlx);
void				clear_screen(t_mlx *mlx);
int					toint(int i, const char *str, int sign);
int					ft_atoi_x(const char *str);
int					check_color(char *str);
int					get_color(int z);
void				ft_lstrev(t_list **alst);
t_mlx				*init(char *title);
void				update_img(t_mlx *mlx);
void				rotate(t_mlx *mlx);
void				render(t_mlx *mlx, t_point **pos);
void				projection_control(t_mlx *mlx, int key);
void				rotate_control(int key, t_mlx *mlx);
void				z_control(int key, t_mlx *mlx);
void				position_control(int key, t_mlx *mlx);
void				zoom_control(int key, t_mlx *mlx);
int					clear(t_mlx *mlx, int y, char *line);
int					exit_x(char *str);
#endif
