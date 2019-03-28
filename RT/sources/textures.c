/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liza <liza@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 13:43:36 by liza              #+#    #+#             */
/*   Updated: 2019/02/02 23:39:01 by liza             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void					load_texture(char *path, cl_uchar4 *dst)
{
	SDL_Surface			*tmp;
	SDL_Surface			*converted_format;

	tmp = IMG_Load(path);
	if (!tmp)
	{
		ft_memset(dst, 0, sizeof(cl_uchar4) * T_S);
		printf("Unable to load image %s! SDL_image Error: %s\n", path,
			IMG_GetError());
	}
	else
	{
		converted_format =
			SDL_ConvertSurfaceFormat(tmp, SDL_PIXELFORMAT_ARGB8888, 0);
		SDL_FreeSurface(tmp);
		ft_memcpy(dst, converted_format->pixels, sizeof(cl_uchar4) * T_S);
		SDL_FreeSurface(converted_format);
	}
}

void					add_textures(t_app *app)
{
	load_texture("resources/brick.bmp", app->texture_pixels.a);
	load_texture("resources/1.jpg", app->texture_pixels.b);
	load_texture("resources/star78.jpeg", app->texture_pixels.c);
}
