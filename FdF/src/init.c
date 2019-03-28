/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmikhajl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 13:42:28 by vmikhajl          #+#    #+#             */
/*   Updated: 2018/03/24 13:42:30 by vmikhajl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"

int			check_color(char *str)
{
	int			i;
	int			color;

	color = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == 'x')
		{
			i++;
			color = ft_atoi_x(str + i);
			break ;
		}
		i++;
	}
	return (color);
}

t_image		*del_image(t_mlx *mlx, t_image *img)
{
	if (img != NULL)
	{
		if (img->img != NULL)
			mlx_destroy_image(mlx->mlx, img->img);
		ft_memdel((void **)&img);
	}
	return (NULL);
}

t_image		*new_image(t_mlx *mlx)
{
	t_image		*img;

	if ((img = ft_memalloc(sizeof(t_image))) == NULL)
		return (NULL);
	if ((img->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT)) == NULL)
		return (del_image(mlx, img));
	img->ptr = mlx_get_data_addr(img->img, &img->bpp, &img->size,
			&img->endian);
	img->bpp /= 8;
	return (img);
}

t_mlx		*mlxdel(t_mlx *mlx)
{
	if (mlx->win != NULL)
		mlx_destroy_window(mlx->mlx, mlx->win);
	if (mlx->image != NULL)
		del_image(mlx, mlx->image);
	ft_memdel((void **)&mlx);
	return (NULL);
}

t_mlx		*init(char *title)
{
	t_mlx		*mlx;

	if ((mlx = ft_memalloc(sizeof(t_mlx))) == NULL)
		return (NULL);
	if ((mlx->mlx = mlx_init()) == NULL ||
		(mlx->win = mlx_new_window(mlx->mlx, WIDTH,
			HEIGHT, title)) == NULL ||
		(mlx->image = new_image(mlx)) == NULL)
		return (mlxdel(mlx));
	free(title);
	return (mlx);
}
