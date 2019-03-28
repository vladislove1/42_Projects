/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_acts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvikhrov <yvikhrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 23:19:57 by liza              #+#    #+#             */
/*   Updated: 2018/09/15 18:27:13 by yvikhrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void				get_file_name(char *file_name)
{
	time_t			rawtime;
	struct tm		*local;

	rawtime = time(0);
	file_name[0] = '\0';
	if (rawtime)
	{
		local = localtime(&rawtime);
		ft_strcpy(file_name, "RT-");
		ft_strcat(file_name, ft_itoa(1900 + local->tm_year));
		ft_strcat(file_name, ft_itoa(local->tm_mon));
		ft_strcat(file_name, ft_itoa(local->tm_mday));
		ft_strcat(file_name, ft_itoa(local->tm_hour));
		ft_strcat(file_name, ft_itoa(local->tm_min));
		ft_strcat(file_name, ft_itoa(local->tm_sec));
		ft_strcat(file_name, ".png");
	}
}

void				screen_shot(t_app *app)
{
	SDL_Surface		*picture;
	char			file_name[50];
	int				pitch;

	if (app)
	{
		pitch = 4 * app->sdl.width;
		picture = SDL_CreateRGBSurfaceFrom(app->sdl.texture,
			app->sdl.width, app->sdl.height, 32, pitch,
			0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);
		get_file_name(file_name);
		if (picture && *file_name)
			IMG_SavePNG(picture, file_name);
		SDL_FreeSurface(picture);
	}
}

void				rotate_camera(t_camera *c, double dt, int motion)
{
	t_q				tmp;

	if (((motion >> 6) & 3) && (dt = ((motion >> 6) & 3) == 1 ? dt : -dt))
	{
		tmp = nrm_q(rot_q(*((t_q*)&c->right), *((t_q*)&c->direction), dt));
		c->right = *(cl_float4*)&tmp;
		tmp = nrm_q(rot_q(*((t_q*)&c->up), *((t_q*)&c->direction), dt));
		c->up = *(cl_float4*)&tmp;
	}
	if (((motion >> 8) & 3) && (dt = ((motion >> 8) & 3) == 1 ? dt : -dt))
	{
		tmp = nrm_q(rot_q(*((t_q*)&c->direction), *((t_q*)&c->up), dt));
		c->direction = *(cl_float4*)&tmp;
		tmp = nrm_q(rot_q(*((t_q*)&c->right), *((t_q*)&c->up), dt));
		c->right = *(cl_float4*)&tmp;
	}
	if (((motion >> 10) & 3) && (dt = ((motion >> 10) & 3) == 1 ? dt : -dt))
	{
		tmp = nrm_q(rot_q(*((t_q*)&c->direction), *((t_q*)&c->right), dt));
		c->direction = *(cl_float4*)&tmp;
		tmp = nrm_q(rot_q(*((t_q*)&c->up), *((t_q*)&c->right), dt));
		c->up = *(cl_float4*)&tmp;
	}
}

void				move_camera(t_camera *c, double dt, int motion)
{
	t_q				tmp;

	dt *= 10;
	if ((motion & 3) && (dt = (motion & 3) == 1 ? dt : -dt))
	{
		tmp = lnr_q(*((t_q*)&c->position), *((t_q*)&c->direction), dt);
		c->position = *(cl_float4*)&tmp;
	}
	if (((motion >> 2) & 3) && (dt = ((motion >> 2) & 3) == 1 ? -dt : dt))
	{
		tmp = lnr_q(*((t_q*)&c->position), *((t_q*)&c->right), dt);
		c->position = *(cl_float4*)&tmp;
	}
	if (((motion >> 4) & 3) && (dt = ((motion >> 4) & 3) == 1 ? dt : -dt))
	{
		tmp = lnr_q(*((t_q*)&c->position), *((t_q*)&c->up), dt);
		c->position = *(cl_float4*)&tmp;
	}
}

void				other_acts(t_app *app, double dt, int *motion)
{
	if (*motion >> 13)
	{
		screen_shot(app);
		*motion &= ~(1 << 13);
	}
	if (*motion >> 12)
	{
		app->scene->camera = app->scene->default_camera;
		*motion &= ~(1 << 12);
	}
}
