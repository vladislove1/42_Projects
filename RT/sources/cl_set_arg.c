/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_set_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvikhrov <yvikhrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 23:19:57 by liza              #+#    #+#             */
/*   Updated: 2018/09/15 18:27:13 by yvikhrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			cl_set_arg_a(t_app *app)
{
	int		err;

	err = 0;
	err |= clSetKernelArg(app->cl.kernel[kGenerateRayKernel]->cl, 0,
		sizeof(cl_mem), &app->cl.pixel_descs->cl);
	err |= clSetKernelArg(app->cl.kernel[kGenerateRayKernel]->cl, 1,
		sizeof(cl_float4), &app->scene->camera.position);
	err |= clSetKernelArg(app->cl.kernel[kGenerateRayKernel]->cl, 2,
		sizeof(cl_float4), &app->scene->camera.right);
	err |= clSetKernelArg(app->cl.kernel[kGenerateRayKernel]->cl, 3,
		sizeof(cl_float4), &app->scene->camera.up);
	err |= clSetKernelArg(app->cl.kernel[kGenerateRayKernel]->cl, 4,
		sizeof(cl_float4), &app->scene->camera.direction);
	err |= clSetKernelArg(app->cl.kernel[kGenerateRayKernel]->cl, 5,
		sizeof(int), &app->sdl.width);
	err |= clSetKernelArg(app->cl.kernel[kGenerateRayKernel]->cl, 6,
		sizeof(int), &app->sdl.height);
	err |= clSetKernelArg(app->cl.kernel[kGenerateRayKernel]->cl, 7,
		sizeof(int), &app->mode);
	return (err);
}

int			cl_set_arg_b(t_app *app)
{
	int		err;

	err = 0;
	err |= clSetKernelArg(app->cl.kernel[kGenerateRayKernel_l]->cl, 0,
		sizeof(cl_mem), &app->cl.pixel_descs_l->cl);
	err |= clSetKernelArg(app->cl.kernel[kGenerateRayKernel_l]->cl, 1,
		sizeof(cl_float4), &app->scene->left_eye.position);
	err |= clSetKernelArg(app->cl.kernel[kGenerateRayKernel_l]->cl, 2,
		sizeof(cl_float4), &app->scene->left_eye.right);
	err |= clSetKernelArg(app->cl.kernel[kGenerateRayKernel_l]->cl, 3,
		sizeof(cl_float4), &app->scene->left_eye.up);
	err |= clSetKernelArg(app->cl.kernel[kGenerateRayKernel_l]->cl, 4,
		sizeof(cl_float4), &app->scene->left_eye.direction);
	err |= clSetKernelArg(app->cl.kernel[kGenerateRayKernel_l]->cl, 5,
		sizeof(int), &app->sdl.width);
	err |= clSetKernelArg(app->cl.kernel[kGenerateRayKernel_l]->cl, 6,
		sizeof(int), &app->sdl.height);
	err |= clSetKernelArg(app->cl.kernel[kGenerateRayKernel_l]->cl, 7,
		sizeof(int), &app->mode);
	return (err);
}

int			cl_set_arg_c(t_app *app)
{
	int		err;

	err = 0;
	err |= clSetKernelArg(app->cl.kernel[kRadianceKernel]->cl, 0,
		sizeof(cl_mem), &app->cl.intersection_descs->cl);
	err |= clSetKernelArg(app->cl.kernel[kRadianceKernel]->cl, 1,
		sizeof(cl_mem), &app->cl.pixel_descs->cl);
	err |= clSetKernelArg(app->cl.kernel[kRadianceKernel]->cl, 2,
		sizeof(cl_mem), &app->cl.objects->cl);
	err |= clSetKernelArg(app->cl.kernel[kRadianceKernel]->cl, 3,
		sizeof(cl_mem), &app->cl.lights->cl);
	err |= clSetKernelArg(app->cl.kernel[kRadianceKernel]->cl, 4,
		sizeof(cl_mem), &app->cl.textures->cl);
	err |= clSetKernelArg(app->cl.kernel[kRadianceKernel]->cl, 5,
		sizeof(int), &app->scene->num_lights);
	err |= clSetKernelArg(app->cl.kernel[kRadianceKernel]->cl, 6,
		sizeof(int), &app->scene->num_objects_to_render);
	err |= clSetKernelArg(app->cl.kernel[kRadianceKernel]->cl, 7,
		sizeof(int), &app->sdl.width);
	err |= clSetKernelArg(app->cl.kernel[kRadianceKernel]->cl, 8,
		sizeof(int), &app->sdl.height);
	return (err);
}

int			cl_set_arg_d(t_app *app)
{
	int		err;

	err = 0;
	err |= clSetKernelArg(app->cl.kernel[kRadianceKernel_l]->cl, 0,
		sizeof(cl_mem), &app->cl.intersection_descs_l->cl);
	err |= clSetKernelArg(app->cl.kernel[kRadianceKernel_l]->cl, 1,
		sizeof(cl_mem), &app->cl.pixel_descs_l->cl);
	err |= clSetKernelArg(app->cl.kernel[kRadianceKernel_l]->cl, 2,
		sizeof(cl_mem), &app->cl.objects->cl);
	err |= clSetKernelArg(app->cl.kernel[kRadianceKernel_l]->cl, 3,
		sizeof(cl_mem), &app->cl.lights->cl);
	err |= clSetKernelArg(app->cl.kernel[kRadianceKernel_l]->cl, 4,
		sizeof(cl_mem), &app->cl.textures->cl);
	err |= clSetKernelArg(app->cl.kernel[kRadianceKernel_l]->cl, 5,
		sizeof(int), &app->scene->num_lights);
	err |= clSetKernelArg(app->cl.kernel[kRadianceKernel_l]->cl, 6,
		sizeof(int), &app->scene->num_objects_to_render);
	err |= clSetKernelArg(app->cl.kernel[kRadianceKernel_l]->cl, 7,
		sizeof(int), &app->sdl.width);
	err |= clSetKernelArg(app->cl.kernel[kRadianceKernel_l]->cl, 8,
		sizeof(int), &app->sdl.height);
	return (err);
}

int			cl_set_arg_e(t_app *app)
{
	int		err;

	err = 0;
	err |= clSetKernelArg(app->cl.kernel[kSaveFrameKernel]->cl, 0,
		sizeof(cl_mem), &app->cl.pixel_descs->cl);
	err |= clSetKernelArg(app->cl.kernel[kSaveFrameKernel]->cl, 1,
		sizeof(cl_mem), &app->cl.pixel_descs_l->cl);
	err |= clSetKernelArg(app->cl.kernel[kSaveFrameKernel]->cl, 2,
		sizeof(cl_mem), &app->cl.image->cl);
	err |= clSetKernelArg(app->cl.kernel[kSaveFrameKernel]->cl, 3,
		sizeof(int), &app->sdl.width);
	err |= clSetKernelArg(app->cl.kernel[kSaveFrameKernel]->cl, 4,
		sizeof(int), &app->sdl.height);
	err |= clSetKernelArg(app->cl.kernel[kSaveFrameKernel]->cl, 5,
		sizeof(int), &app->mode);
	return (err);
}
