/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvikhrov <yvikhrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 23:19:57 by liza              #+#    #+#             */
/*   Updated: 2018/09/15 18:27:13 by yvikhrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "gui.h"
#include <mach/mach_time.h>

void							init_timer(t_timer *timer)
{
	mach_timebase_info_data_t	coeff;

	mach_timebase_info(&coeff);
	timer->numer = coeff.numer;
	timer->denom = coeff.denom;
	timer->current_time = 0;
	timer->start = mach_absolute_time();
	timer->current = timer->start;
	timer->time = 0.0;
	timer->old_time = 0.0;
}

double							get_delta_time(t_timer *timer)
{
	double						delta_time;

	timer->current = mach_absolute_time() - timer->start;
	timer->current_time = timer->current * timer->numer / timer->denom;
	timer->time = (double)(timer->current_time / 1000) / 1000000.0;
	delta_time = timer->time - timer->old_time;
	timer->old_time = timer->time;
	return (delta_time);
}

void							process_event(t_app *app, double dt)
{
	SDL_Event					e;
	static int					motion = 0;

	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN &&
				e.key.keysym.scancode == SDL_SCANCODE_ESCAPE))
			app->sdl.quit = true;
		else if (e.type == SDL_KEYDOWN)
		{
			recognize_motion(&motion, e.key.keysym.scancode);
			recognize_mode(&app->mode, e.key.keysym.scancode);
		}
		else if (e.type == SDL_KEYUP)
			reset_motion(&motion, e.key.keysym.scancode);
		process_gui_event(&e);
	}
	rotate_camera(&app->scene->camera, dt, motion);
	move_camera(&app->scene->camera, dt, motion);
	other_acts(app, dt, &motion);
	init_left_eye(app);
}

void							render(t_app *app)
{
	int							err;

	err = 0;
	err |= cl_set_arg_a(app);
	err |= cl_set_arg_b(app);
	err |= cl_set_arg_c(app);
	err |= cl_set_arg_d(app);
	err |= cl_set_arg_e(app);
	err |= cl_kernel_run(app->cl.cl, app->cl.kernel[kGenerateRayKernel],
		app->sdl.width, app->sdl.height);
	err |= cl_kernel_run(app->cl.cl, app->cl.kernel[kGenerateRayKernel_l],
		app->sdl.width, app->sdl.height);
	err |= cl_kernel_run(app->cl.cl, app->cl.kernel[kRadianceKernel],
		app->sdl.width, app->sdl.height);
	err |= cl_kernel_run(app->cl.cl, app->cl.kernel[kRadianceKernel_l],
		app->sdl.width, app->sdl.height);
	err |= cl_kernel_run(app->cl.cl, app->cl.kernel[kSaveFrameKernel],
		app->sdl.width, app->sdl.height);
	cl_buffer_read(app->cl.cl, app->cl.image, 4 * app->sdl.width *
		app->sdl.height, app->sdl.texture);
	if (!err)
		ft_putendl("kernel run warning");
}

void							main_loop(t_app *app)
{
	double						dt;

	get_delta_time(&app->timer);
	while (!app->sdl.quit)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		dt = get_delta_time(&app->timer);
		process_event(app, dt);
		render(app);
		glUseProgram(app->sdl.program_id);
		glBindVertexArray(app->sdl.vao);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindTexture(GL_TEXTURE_2D, app->sdl.texture_id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, app->sdl.width, app->sdl.height,
			0, GL_RGBA, GL_UNSIGNED_BYTE, app->sdl.texture);
		render_gui(app);
		SDL_GL_SwapWindow(app->sdl.window);
	}
}
