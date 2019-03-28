/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmikhajl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 13:42:28 by vmikhajl          #+#    #+#             */
/*   Updated: 2018/03/24 13:42:30 by vmikhajl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		pixel_put(t_image *image, int x, int y, t_point *p)
{
	int			i;

	if ((x > 0 && x < WIDTH) && (y > 0 && y < HEIGHT))
	{
		i = image->bpp * (x + y * WIDTH);
		image->ptr[i] = p->b;
		image->ptr[++i] = p->g;
		image->ptr[++i] = p->r;
	}
	free(p);
}

t_point		*col(t_point p1, t_point p2)
{
	t_point		*ret;

	ret = malloc(sizeof(t_point));
	ret->r = p1.r;
	ret->g = p1.g;
	ret->b = p1.b;
	if (p1.b > 0)
		ret->b = p1.b;
	if (p1.r > 0)
		ret->r = p1.r;
	if (p1.color != p2.color)
	{
		if (p1.g > 0)
		{
			ret->g = p2.g;
			ret->r = p2.r;
			ret->b = p2.b;
		}
	}
	return (ret);
}

void		draw_line(t_point p1, t_point p2, t_mlx *mlx)
{
	t_bras		b;

	b.dx = abs((int)p2.x - (int)p1.x);
	b.dy = -abs((int)p2.y - (int)p1.y);
	b.sx = p1.x < p2.x ? 1 : -1;
	b.sy = p1.y < p2.y ? 1 : -1;
	b.err = b.dx + b.dy;
	while (1)
	{
		pixel_put(mlx->image, p1.x + mlx->control.right,
		p1.y + mlx->control.up, col(p1, p2));
		if (p1.x == p2.x && p1.y == p2.y)
			break ;
		b.e2 = 2 * b.err;
		if (b.e2 >= b.dy)
		{
			b.err += b.dy;
			p1.x += b.sx;
		}
		if (b.e2 <= b.dx)
		{
			b.err += b.dx;
			p1.y += b.sy;
		}
	}
}

void		render(t_mlx *mlx, t_point **pos)
{
	int			i;
	int			j;

	j = 0;
	while (j < mlx->index - 1)
	{
		i = 0;
		while (i < mlx->width - 1)
		{
			draw_line(pos[j][i], pos[j][i + 1], mlx);
			draw_line(pos[j][i], pos[j + 1][i], mlx);
			i++;
		}
		draw_line(pos[j][i], pos[j + 1][i], mlx);
		j++;
	}
	while (i > 0)
	{
		draw_line(pos[j][i], pos[j][i - 1], mlx);
		i--;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->image->img, 0, 0);
}

void		update_img(t_mlx *mlx)
{
	int			i;

	i = 0;
	while (i < mlx->index)
		free(mlx->point[i++]);
	free(mlx->point);
	if ((mlx->point = (t_point **)malloc(sizeof(t_point **) * mlx->index)))
		get_map(mlx, mlx->lst, mlx->point);
	rotate(mlx);
	mlx_destroy_image(mlx->mlx, mlx->image->img);
	mlx->image->img = mlx_new_image(mlx->mlx, 1900, 1200);
	mlx->image->ptr = mlx_get_data_addr(mlx->image->img, &mlx->image->bpp,
		&mlx->image->size, &mlx->image->endian);
	mlx->image->bpp /= 8;
	render(mlx, mlx->point);
	mlx_string_put(mlx->mlx, mlx->win, 20, 10, 0xFF, "r_y    - key 2 | key  5");
	mlx_string_put(mlx->mlx, mlx->win, 20, 30, 0xFF, "r_x    - key 1 | key  4");
	mlx_string_put(mlx->mlx, mlx->win, 20, 50, 0xFF, "zoom   - key + | key  -");
	mlx_string_put(mlx->mlx, mlx->win, 20, 70, 0xFF, "height - key Z | key  X");
	mlx_string_put(mlx->mlx, mlx->win, 20, 90, 0xFF, "cancel - key 1 | key  2");
}
