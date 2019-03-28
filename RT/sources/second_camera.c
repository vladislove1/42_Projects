/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvikhrov <yvikhrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 23:19:57 by liza              #+#    #+#             */
/*   Updated: 2018/09/15 18:27:13 by yvikhrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <stdio.h>

void		set_aa_mode(t_camera *c, t_camera *c_l, double k)
{
	t_q		tmp;
	t_q		axis;

	c_l->position = c->position;
	axis = rot_q(*((t_q*)&c->right), *((t_q*)&c->direction), atan(-1.0f));
	tmp = nrm_q(rot_q(*((t_q*)&c->direction), axis, k));
	c_l->direction = *(cl_float4*)&tmp;
	tmp = nrm_q(rot_q(*((t_q*)&c->right), axis, k));
	c_l->right = *(cl_float4*)&tmp;
	tmp = nrm_q(rot_q(*((t_q*)&c->up), axis, k));
	c_l->up = *(cl_float4*)&tmp;
}

void		set_shifted_mode(t_camera *c, t_camera *c_l)
{
	t_q		tmp;

	tmp = add_q((t_q){-2.0f, 0.0f, -2.0f, 0.0f}, *((t_q*)&c->position));
	c_l->position = *(cl_float4*)&tmp;
	c_l->direction = c->direction;
	c_l->right = c->right;
	c_l->up = c->up;
}

void		set_gliph_mode(t_camera *c, t_camera *c_l)
{
	t_q		tmp;
	float	dist_between_eyes;
	float	turn_left_eye;

	dist_between_eyes = -0.5f;
	turn_left_eye = 0.03f;
	tmp = lnr_q(*((t_q*)&c->position), *((t_q*)&c->right), dist_between_eyes);
	c_l->position = *(cl_float4*)&tmp;
	tmp = nrm_q(rot_q(*((t_q*)&c->direction), *((t_q*)&c->up), turn_left_eye));
	c_l->direction = *(cl_float4*)&tmp;
	tmp = nrm_q(rot_q(*((t_q*)&c->right), *((t_q*)&c->up), turn_left_eye));
	c_l->right = *(cl_float4*)&tmp;
	c_l->up = c->up;
}

void		init_left_eye(t_app *app)
{
	int		camera_mode;
	float	k;

	camera_mode = app->mode >> 4;
	if (app->scene->left_eye.initialized == false)
	{
		if (camera_mode == 4)
			set_shifted_mode(&app->scene->camera, &app->scene->left_eye);
		else if (camera_mode == 1)
		{
			k = atan(0.5f / app->sdl.width);
			set_aa_mode(&app->scene->camera, &app->scene->left_eye, k);
		}
		else if (camera_mode == 2)
			set_gliph_mode(&app->scene->camera, &app->scene->left_eye);
		else
		{
			app->scene->left_eye.position = app->scene->camera.position;
			app->scene->left_eye.direction = app->scene->camera.direction;
			app->scene->left_eye.right = app->scene->camera.right;
			app->scene->left_eye.up = app->scene->camera.up;
		}
	}
}
