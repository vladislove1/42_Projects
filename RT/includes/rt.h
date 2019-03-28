/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvikhrov <yvikhrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 14:11:35 by yvikhrov          #+#    #+#             */
/*   Updated: 2018/09/15 18:24:57 by yvikhrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <GL/glew.h>
# include <SDL.h>
# include <SDL_opengl.h>
# include <SDL_image.h>
# include <stdint.h>
# include <math.h>
# include <stdbool.h>
# include <time.h>
# include "quaternion.h"
# include "libft.h"
# include "get_next_line.h"
# include "cl.h"
# include "parser.h"

# define T_W 		512
# define T_S 		262144

typedef struct				s_timer
{
	uint64_t				start;
	uint64_t				current;
	uint64_t				current_time;
	uint64_t				numer;
	uint64_t				denom;
	double					time;
	double					old_time;
}							t_timer;

void						init_timer(t_timer *timer);
struct s_scene;

typedef struct				s_texture
{
	cl_uchar4				a[T_S];
	cl_uchar4				b[T_S];
	cl_uchar4				c[T_S];
}							t_texture;

typedef struct				s_sdl
{
	SDL_GLContext			gl_context;
	SDL_Window				*window;
	void					*texture;
	GLuint					texture_id;
	GLuint					program_id;
	GLuint					vbo;
	GLuint					vao;
	int						width;
	int						height;
	float					window_aspect;
	bool					quit;
}							t_sdl;

struct s_scene;

struct						s_ray
{
	cl_float4				o;
	cl_float4				d;
};

struct						s_pixel_desc
{
	struct s_ray			ray;
	cl_float4				radiance;
};

struct						s_intersection_desc
{
	cl_float4				normal;
	cl_float				t;
	cl_int					intersected_obj;
};

enum
{
	kKernelsBegin = 0,
	kRadianceKernel = 0,
	kRadianceKernel_l,
	kGenerateRayKernel,
	kGenerateRayKernel_l,
	kSaveFrameKernel,
	kKernelsNum
};

struct						s_cl_container
{
	struct s_cl				*cl;
	struct s_cl_buffer		*image;
	struct s_cl_buffer		*objects;
	struct s_cl_buffer		*lights;
	struct s_cl_buffer		*textures;
	struct s_cl_buffer		*pixel_descs;
	struct s_cl_buffer		*intersection_descs;
	struct s_cl_buffer		*pixel_descs_l;
	struct s_cl_buffer		*intersection_descs_l;
	struct s_cl_kernel		*kernel[kKernelsNum];
};

typedef struct				s_app
{
	t_sdl					sdl;
	struct s_cl_container	cl;
	struct s_scene			*scene;
	char					key_mask[282];
	t_timer					timer;
	cl_int					mode;
	void					*gui;
	t_texture				texture_pixels;
}							t_app;

int							cl_set_arg_a(t_app *app);
int							cl_set_arg_b(t_app *app);
int							cl_set_arg_c(t_app *app);
int							cl_set_arg_d(t_app *app);
int							cl_set_arg_e(t_app *app);

void						reset_motion(int *motion, int scancode);
void						recognize_motion(int *motion, int scancode);
void						recognize_mode(int *mode, int scancode);

void						get_file_name(char *file_name);
void						screen_shot(t_app *app);
void						rotate_camera(t_camera *c, double dt, int motion);
void						move_camera(t_camera *c, double dt, int motion);
void						other_acts(t_app *app, double dt, int *motion);

void						set_aa_mode(t_camera *c, t_camera *c_l, double k);
void						set_shifted_mode(t_camera *c, t_camera *c_l);
void						set_gliph_mode(t_camera *c, t_camera *c_l);
void						init_left_eye(t_app *app);

void						load_texture(char *path, cl_uchar4 *dst);
void						add_textures(t_app *app);

struct s_light				*init_lights_array(struct s_list *light,
																int num_lights);
bool						update_lights_buffers(t_app *app);
void						remove_light(t_app *app, int light_index);
int							count_implicit_objects_num(struct s_list *head);

void						add_disk_to_cone(struct s_obj *cone);
void						add_disk_to_cylinder(struct s_obj *cylinder);
struct s_obj				*init_objects_array(struct s_list *primitives,
														int *num_primitives);
bool						update_object_buffers(t_app *app);
void						remove_object(t_app *app, int object_index);

size_t						read_file_fd(int fd, char **file);
size_t						read_file(char *path, char **file);

bool						all_cl_buffer_init(t_app *app);
bool						init_cl(t_app *app);
bool						init_gl(t_sdl *sdl);
bool						init_sdl(t_sdl *sdl);
bool						init(t_app *app, char *scene_path);

void						init_timer(t_timer *timer);
double						get_delta_time(t_timer *timer);
void						process_event(t_app *app, double dt);
void						render(t_app *app);
void						main_loop(t_app *app);

#endif
