/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liza <liza@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 13:43:36 by liza              #+#    #+#             */
/*   Updated: 2019/02/02 23:39:01 by liza             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "gui.h"
#include <stdio.h>

char *g_kernel_names[kKernelsNum] =
{
	"Radiance",
	"Radiance",
	"GenerateRay",
	"GenerateRay",
	"SaveFrame"
};

bool					all_cl_buffer_init(t_app *app)
{
	struct s_light		*lights;

	lights = init_lights_array(app->scene->lights, app->scene->num_lights);
	if (!lights)
		return (false);
	app->cl.lights = cl_buffer_init(app->cl.cl, sizeof(struct s_light) *
		app->scene->num_lights, lights);
	free(lights);
	update_object_buffers(app);
	app->cl.pixel_descs = cl_buffer_init(app->cl.cl,
		sizeof(struct s_pixel_desc) * app->sdl.width * app->sdl.height, NULL);
	app->cl.intersection_descs = cl_buffer_init(app->cl.cl,
		sizeof(struct s_intersection_desc) * app->sdl.width * app->sdl.height,
		NULL);
	app->cl.pixel_descs_l = cl_buffer_init(app->cl.cl,
		sizeof(struct s_pixel_desc) * app->sdl.width * app->sdl.height, NULL);
	app->cl.intersection_descs_l = cl_buffer_init(app->cl.cl,
		sizeof(struct s_intersection_desc) * app->sdl.width * app->sdl.height,
		NULL);
	app->cl.textures = cl_buffer_init(app->cl.cl, sizeof(t_texture),
		&app->texture_pixels);
	app->cl.image = cl_buffer_init(app->cl.cl, sizeof(cl_uchar4) *
		app->sdl.width * app->sdl.height, NULL);
	return (true);
}

bool					init_cl(t_app *app)
{
	char				*source;
	size_t				size;
	int					i;

	i = kKernelsBegin;
	size = read_file("kernel.cl", &source);
	if (!size)
		return (false);
	app->cl.cl = cl_init(source, size);
	free(source);
	if (!app->cl.cl)
		return (false);
	if (!all_cl_buffer_init(app))
		return (false);
	while (i < kKernelsNum)
	{
		app->cl.kernel[i] = cl_kernel_init(app->cl.cl, g_kernel_names[i]);
		if (!app->cl.kernel[i])
			return (false);
		++i;
	}
	if (!app->cl.cl || !app->cl.objects || !app->cl.lights || !app->cl.image)
		return (false);
	return (true);
}

const char g_fragment_shader[] =
"#version 330 core                    \n"
"out vec4 FragColor;                  \n"
"in vec2 uv;                          \n"
"                                     \n"
"uniform sampler2D sampler;           \n"
"void main()                          \n"
"{                                    \n"
"    FragColor = texture(sampler, uv);\n"
"}                                    \n";

const char g_vertex_shader[] =
"#version 330 core                      \n"
"layout (location = 0) in vec2 aPos;    \n"
"layout (location = 1) in vec2 aUV;     \n"
"                                       \n"
"out vec2 uv;                           \n"
"void main()                            \n"
"{                                      \n"
"    gl_Position = vec4(aPos, 0.0, 1.0);\n"
"    uv = aUV;                          \n"
"}                                      \n";

float g_vertices[] = {
	1.0f, 1.0f, 1.0f, 0.0f,
	1.0f, -1.0f, 1.0f, 1.0f,
	-1.0f, -1.0f, 0.0f, 1.0f,
	-1.0f, 1.0f, 0.0f, 0.0f,
	1.0f, 1.0f, 1.0f, 0.0f,
	-1.0f, -1.0f, 0.0f, 1.0f
};

bool					init_gl(t_sdl *sdl)
{
	glGenTextures(1, &sdl->texture_id);
	glBindTexture(GL_TEXTURE_2D, sdl->texture_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sdl->width, sdl->height, 0, GL_RGBA,
		GL_UNSIGNED_BYTE, NULL);
	if (!(sdl->program_id = gl_compile_program(g_vertex_shader,
			g_fragment_shader)))
		return (false);
	glGenVertexArrays(1, &sdl->vao);
	glBindVertexArray(sdl->vao);
	glGenBuffers(1, &sdl->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, sdl->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertices), g_vertices,
		GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float),
		(void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float),
		(void*)(2 * sizeof(float)));
	return (true);
}

bool					init_sdl(t_sdl *sdl)
{
	sdl->height = 800;
	sdl->width = 800;
	sdl->window_aspect = (float)(sdl->width) / sdl->height;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		ft_putendl("Unable to initialize SDL.");
		return (false);
	}
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
		SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	if ((sdl->window = SDL_CreateWindow("RT", 100, 100, sdl->width,
		sdl->height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL)) == NULL)
	{
		ft_putendl("Unable to create SDL window.");
		return (false);
	}
	if (!init_gui(sdl))
		return (false);
	sdl->texture = malloc(sdl->width * sdl->height * 4);
	return (true);
}

bool					init(t_app *app, char *scene_path)
{
	app->scene = parse_scene(scene_path);
	if (!app->scene || !init_sdl(&app->sdl))
		return (false);
	init_left_eye(app);
	if (!init_gl(&app->sdl))
		return (false);
	add_textures(app);
	if (!init_cl(app))
		return (false);
	app->scene->camera.initialized = false;
	app->mode = 0x00;
	init_timer(&app->timer);
	return (true);
}
